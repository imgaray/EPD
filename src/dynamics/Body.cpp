#ifndef BODY_CP
#define BODY_CPP
#include "Body.h"
#include <assert.h>
#include "CtsDynamics.h"
#include <cmath>

/* USE std::max(x,y), it's a macro i think: max(x, y) ((x) > (y)?(x):(y))
static inline double max(double one, double other) {
	return (one >= other) ? one : other;
}
*/
Body::Body(double mass) :
		position(), linear_velocity(), angular_velocity() {
	this->angle = 0;
	this->linear_damping = 0;
	this->angular_damping = 0;
	this->gravity = 0;
	this->mass = mass;
	this->inertia_moment = mass;
	this->shape = NULL;
}
Body::Body(double mass, Vec& position) :
		position(position), linear_velocity(), angular_velocity() {
	this->angle = 0;
	this->linear_damping = 0;
	this->angular_damping = 0;
	this->gravity = 0;

	this->mass = mass;
	this->inertia_moment = mass;
	this->shape = NULL;
}
Body::~Body() {
	if (this->shape)
		delete shape;
}

void Body::applyForce(const Force& force) {
	this->force += force;
}
void Body::applyForce(const Force& force, const Vec& point) {
	this->applyForce(force);
	this->applyTorque(force.getToque(point - this->position));
}
void Body::applyTorque(const Torque& torque) {
	this->torque += torque;
}

void Body::applyLinearImpulse(Vec& impulse) {
	this->linear_velocity += (impulse / (this->mass));
}

void Body::applyAngularImpulse(Vec& impulse) {
	this->angular_velocity += (impulse / (this->mass));
}

void Body::applyImpulse(Vec& impulse, const Vec& point) {
	this->applyLinearImpulse(impulse);
	this->angular_velocity += (point - this->position) ^ (impulse) / this->mass;
}

Vec& Body::getPosition() {
	Vec* vec = new Vec();
	return *vec;
}
Vec& Body::getLinearVelocity() {
	return this->linear_velocity;
}
Vec& Body::getAngularVelocity() {
	return this->angular_velocity;
}
double Body::getMass() {
	return this->mass;
}
double Body::getInertiaMoment() {
	return this->inertia_moment;
}
double Body::getAngle() {
	return this->angle;
}
double Body::getGravity() {
	return this->gravity;
}

inline bool Body::inContact(const Body& other) const {
	Vec* contact = new Vec[2];
	Vec* norm = new Vec[2];
	double penetration[2];
	size_t count = 0;
	return this->shape->touches((Touchable&) (*(other.shape)), contact, norm, penetration, count);
}

// this is an adaption of the following algorithm:
// http://www.plasmaphysics.org.uk/programs/coll2d_cpp.htm
void Body::collide(Body& other) {
	assert(other.shape && this->shape);
	Vec* contact = new Vec[2];
	Vec* norm = new Vec[2];
	double penetration[2];
	size_t count = 0;
	if (!this->shape->touches((Touchable&) (*(other.shape)), contact, norm, penetration, count))
		return;
	// here on, we assume that the collision is an elastic one,
	// could be modified later without changing the collide interface
	// Two basic principles involved here: conservation of linear Momentum
	// and conservation of Kinetic energy
	double m21, dvx2, a, fy21, sign, R;
	// Almost perfectly elastic collision, this factor R is the restitution
	// coefficient. Must be between 1 and 0
	Vec v_cm, r21, v21;
	R = 0.99;
	if (!other.mass)
		return;
	// mass ratio
	m21 = this->mass / other.mass;
	// relative distance
	r21 = other.position - this->position;
	// relative velocities
	v21 = this->linear_velocity - other.linear_velocity;
	// the velocity of the center of mass of both bodies united
	v_cm = (this->linear_velocity * this->mass
			+ other.linear_velocity * other.mass) / (this->mass + other.mass);
// return old velocities if bodies are not approaching
	if ((v21 * r21) >= 0)
		return;

// Author notes:
// I have inserted the following statements to avoid a zero divide; 
// (for single precision calculations, 
// 1.0E-12 should be replaced by a larger value).  

	fy21 = 1.0E-12 * fabs(r21.y);
	if (fabs(r21.x) < fy21) {
		sign = (r21.x < 0) ? -1 : 1;
		r21.x = fy21 * sign;
	}

// update velocities
	a = r21.y / r21.x;
	dvx2 = -2 * (v21.x + a * v21.y) / ((1 + a * a) * (1 + m21));
	other.linear_velocity.x = other.linear_velocity.x + dvx2;
	other.linear_velocity.y = other.linear_velocity.y + a * dvx2;
	this->linear_velocity.x = this->linear_velocity.x - m21 * dvx2;
	this->linear_velocity.y = this->linear_velocity.y - a * m21 * dvx2;

// velocity correction for inelastic collisions
	this->linear_velocity = (this->linear_velocity - v_cm) * R + v_cm;
	other.linear_velocity = (other.linear_velocity - v_cm) * R + v_cm;

	/*
	 // TODO: see the way to get the contact point and the normal point of
	 // collision
	 Vec contact;
	 Vec normal;
	 double m1 = 1/this->mass;
	 double m2 = 1/other.mass;
	 double im1 = 1 / this->inertial_mass;
	 double im2 = 1 / other.inertial_mass;
	 Vec r1 = this->position - contact;
	 Vec r2 = other.position - contact;
	 Vec v1 = this->linear_velocity + this->angular_velocity ^ r1;
	 Vec v2 = other.linear_velocity + other.angular_velocity ^ r2;
	 Vec dv = v1 - v2;
	 double Kn = m1 + m2 + ((r1 ^ normal) ^ r1 * im1 +
	 (r2 ^ normal) ^ r2 * im2) * normal;
	 Vec Pn = normal * max(-dv * normal / Kn, 0);
	 this->linear_velocity += Pn * m1;
	 this->angular_velocity += r1 ^ Pn * im1;
	 other.linear_velocity -= Pn * m2;
	 other.angular_velocity -= r2 ^ Pn * im2;
	 // TODO: tangential part of P.
	 // See: http://www.xbdev.net/physics/RigidBodyImpulseCubes/index.php
	 */
}

void Body::setPosition(Vec& pos) {
	this->position = pos;
}
void Body::setLinearVelocity(Vec& vel) {
	this->linear_velocity = vel;
}
void Body::setAngularVelocity(Vec& vel) {
	this->angular_velocity = vel;
}
void Body::setInertiaMoment(double inertia_moment) {
	this->inertia_moment = inertia_moment;
}
void Body::setAngle(double angle) {
	this->angle = angle;
}
void Body::setGravity(double gravity) {
	this->gravity = gravity;
}

void Body::setShape(Shape* shape) {
	if (this->shape)
		delete shape;
	this->shape = shape;
}

#endif
