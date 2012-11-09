#ifndef BODY_H
#define BODY_H

#include <cstring>
#include "Math.h"
#include "Force.h"
#include "Shape.h"

class Body {
private:
	// this should be the Center of Mass position.
	Vec position;
	double angle;
	// This is the velocity of the center of mass.
	Vec linear_velocity;
	Vec angular_velocity;
	// The net forces applied to the body
	Force force;
	Torque torque;
	// The shape should determine the inertia_moment
	Shape* shape;
	double linear_damping;
	double angular_damping;
	double gravity;

	double mass;
	double inertia_moment;
public:
	Body(double mass);
	Body(double mass, Vec& position);
	virtual ~Body();
	
	// for front-end purposes
	bool inContact(const Body& other) const;
	void applyForce(const Force& f);
	void applyForce(const Force& f, const Vec& point);
	void applyTorque(const Torque& t);
	void collide(Body& other);
	// this is useful for collisions
	void applyLinearImpulse(Vec& impulse);
	void applyAngularImpulse(Vec& impulse);
	void applyImpulse(Vec& impulse, const Vec& point);

	/*GETTERS & SETTERS*/
	Vec& getPosition();
	Vec& getLinearVelocity();
	Vec& getAngularVelocity();
	double getMass();
	double getInertiaMoment();
	double getAngle();
	double getGravity();
	void setShape(Shape* shape);

	void setPosition(Vec& pos);
	void setLinearVelocity(Vec& vel);
	void setAngularVelocity(Vec& vel);
	void setInertiaMoment(double inertia_moment);
	void setAngle(double angle);
	void setGravity(double gravity);
};

#endif
