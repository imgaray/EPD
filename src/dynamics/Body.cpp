#ifndef BODY_CP
#define BODY_CPP
#include "Body.h"
#include <assert.h>
#include "CtsDynamics.h"

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
	return this->shape->touches((Touchable&)(*(other.shape)));
}

// this is an adaption of the following algorithm:
// http://www.plasmaphysics.org.uk/programs/coll2d_cpp.htm
void Body::collide(Body& other) {
	assert(other.shape && this->shape);
	if (!this->inContact(other))
		return;
	// here on, we assume that the collision is an elastic one,
	// could be modified later without changing the collide interface
	// Two basic principles involved here: conservation of linear Momentum
	// and conservation of Kinetic energy
    double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;
	if (!other.mass) return;
	// mass ratio
	m21=this->mass/other.mass;
	// relative distance
    x21=other.position.x-this->position.x;
    y21=other.position.y-this->position.y;
    // relative velocities
    vx21=this->getLinearVelocity().x-other.getLinearVelocity().x;
    vy21=this->getLinearVelocity().y-other.getLinearVelocity().y;
	// the velocity of the center of mass of both bodies united
    vx_cm = (this->mass * this->getLinearVelocity().x + 
					other.mass*other.getLinearVelocity().x)
					/(this->mass + other.mass);
    vy_cm = (this->mass * this->getLinearVelocity().y + 
					other.mass*other.getLinearVelocity().y)
					/(this->mass + other.mass);


// return old velocities if bodies are not approaching
    if ((vx21 * x21 + vy21 * y21) >= 0) return;

// Author notes:
// I have inserted the following statements to avoid a zero divide; 
// (for single precision calculations, 
// 1.0E-12 should be replaced by a larger value).  
  
	fy21 = 1.0E - 12 * fabs(y21);                            
	if (fabs(x21) < fy21) {  
		sign = (x21 < 0)? -1 : 1;  
		x21 = fy21 * sign; 
	} 

// update velocities
	a = y21 / x21;
	dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21));
	other.getLinearVelocity().x = other.getLinearVelocity().x + dvx2;
	other.getLinearVelocity().y = other.getLinearVelocity().y + a * dvx2;
	this->getLinearVelocity().x = this->getLinearVelocity().y - m21 * dvx2;
	this->getLinearVelocity().x = this->getLinearVelocity().y - a * m21 * dvx2;

// velocity correction for inelastic collisions
	this->getLinearVelocity().x = (this->getLinearVelocity().x - vx_cm) * R + vx_cm;
	this->getLinearVelocity().y = (this->getLinearVelocity().y - vy_cm) * R + vy_cm;
	other.getLinearVelocity().x = (other.getLinearVelocity().x - vx_cm) * R + vx_cm;
	other.getLinearVelocity().y = (other.getLinearVelocity().y - vy_cm) * R + vy_cm;
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
