#ifndef BODY_H
#define BODY_H

#include "../common/Math.h"
#include "./Force.h"

class Body {
private:
	Vec position;	
	double angle;
	Vec linear_velocity;
	Vec angular_velocity;
	Force force;
	Torque torque;

	double linear_damping;
	double angular_damping;
	double gravity;

	double mass;
	double inertia_moment;
public:
	Body(double mass);
	Body(double mass, Vec& position);
	virtual ~Body();	

	void applyForce(const Force& f);
	void applyForce(const Force& f, const Vec& point);

	void applyTorque(const Torque& t);

	// this is useful for collisions
	void applyImpulse(Vec& impulse);
	void applyImpulse(Vec& impulse, const Vec& point);

	/*GETTERS & SETTERS*/
	Vec& getPosition();
	Vec& getLinearVelocity();
	Vec& getAngularVelocity();
	double getMass();
	double getInertiaMoment();
	double getAngle();
	double getGravity();

	void setPosition(Vec& pos);
	void setLinearVelocity(Vec& vel);
	void setAngularVelocity(Vec& vel);
	void setInertiaMoment(double inertia_moment);
	void setAngle(double angle);
	void setGravity(double gravity);
};

#endif
