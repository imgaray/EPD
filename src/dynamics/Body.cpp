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
	m21=this->mass/other.mass;
    x21=other.position.x-this->position.x;
    y21=other.position.y-this->position.y;
    vx21=this->getLinearVelocity().x-other.getLinearVelocity().x;
    vy21=this->getLinearVelocity().y-other.getLinearVelocity().y;

    vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
    vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;   


//     *** return old velocities if balls are not approaching ***
    if ( (vx21*x21 + vy21*y21) >= 0) return;


//     *** I have inserted the following statements to avoid a zero divide; 
//         (for single precision calculations, 
//          1.0E-12 should be replaced by a larger value). **************  
  
       fy21=1.0E-12*fabs(y21);                            
       if ( fabs(x21)<fy21 ) {  
                   if (x21<0) { sign=-1; } else { sign=1;}  
                   x21=fy21*sign; 
        } 

//     ***  update velocities ***
       a=y21/x21;
       dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
       vx2=vx2+dvx2;
       vy2=vy2+a*dvx2;
       vx1=vx1-m21*dvx2;
       vy1=vy1-a*m21*dvx2;

//     ***  velocity correction for inelastic collisions ***
       vx1=(vx1-vx_cm)*R + vx_cm;
       vy1=(vy1-vy_cm)*R + vy_cm;
       vx2=(vx2-vx_cm)*R + vx_cm;
       vy2=(vy2-vy_cm)*R + vy_cm;
   
       return;
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
