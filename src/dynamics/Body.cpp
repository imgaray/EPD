#ifndef BODY_CP
#define BODY_CPP
#include "Body.h"

Body::Body(double mass) : position(*(new Vec(0,0))),
		linear_velocity(0, 0), angular_velocity(0, 0) {
	this->angle = 0;
	this->linear_damping = 0;
	this->angular_damping = 0;
	this->gravity = 0;
	this->mass = mass;
	this->inertia_moment = mass;
}
Body::Body(double mass, Vec& position) : position(position),
		linear_velocity(0, 0), angular_velocity(0, 0) {
	this->angle = 0;
	this->linear_damping = 0;
	this->angular_damping = 0;
	this->gravity = 0;

	this->mass = mass;
	this->inertia_moment = mass;
}
Body::~Body() {
}

void Body::applyForce(const Force& force) {
}
void Body::applyForce(const Force& force, const Vec& point) {
}
void Body::applyTorque(const Torque& torque) {
}
void Body::applyImpulse(Vec& impulse) {
}
void Body::applyImpulse(Vec& impulse, const Vec& point) {
}

Vec& Body::getPosition() {
	return this->position;
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
	return 0;
}
double Body::getGravity() {
	return 0;
}

void Body::setPosition(Vec& pos) {
}
void Body::setLinearVelocity(Vec& vel) {
}
void Body::setAngularVelocity(Vec& vel) {
}
void Body::setInertiaMoment(double inertia_moment) {
}
void Body::setAngle(double angle) {
}
void Body::setGravity(double gravity) {
}
#endif
