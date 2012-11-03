#ifndef BODY_CP
#define BODY_CPP
#include "Body.h"

Body::Body(double mass) :
		position(), linear_velocity(), angular_velocity() {
	this->angle = 0;
	this->linear_damping = 0;
	this->angular_damping = 0;
	this->gravity = 0;
	this->mass = mass;
	this->inertia_moment = mass;
}
Body::Body(double mass, Vec& position) :
		position(position), linear_velocity(), angular_velocity() {
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
	this->force += force;
}
void Body::applyForce(const Force& force, const Vec& point) {
	this->applyForce(force);
	this->applyTorque(force.getToque(point));
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
	this->angular_velocity += point.cross(impulse) / this->mass;
}

Vec& Body::getPosition() {
	Vec* vec = new Vec();
	return *vec;
}
Vec& Body::getLinearVelocity() {
	Vec* vec = new Vec();
	return *vec;
}
Vec& Body::getAngularVelocity() {
	Vec* vec = new Vec();
	return *vec;
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

void Body::setPosition(Vec& pos) {
	delete &this->position;
	this->position = pos;
}
void Body::setLinearVelocity(Vec& vel) {
	delete &this->linear_velocity;
	this->linear_velocity = vel;
}
void Body::setAngularVelocity(Vec& vel) {
	delete &this->angular_velocity;
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
#endif
