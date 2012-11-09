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
	return this->shape->touches(*(other.shape));
}

void Body::collide(Body& other) {
	assert(other.shape && this->shape);
	if (!this->inContact(other))
		return;
	// here on, we assume that the collision is an elastic one,
	// could be modified later without changing the collide interface
	// Two basic principles involved here: conservation of linear Momentum
	// and conservation of Kinetic energy

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
