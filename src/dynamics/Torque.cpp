#ifndef TORQUE_CPP
#define TORQUE_CPP
#include "Torque.h"

Torque::Torque(double x, double y, double z):Vec(x,y,z){}

Torque::~Torque(){}

/**
*	Gets the linear acceleration that the force causes to the mass.
*	@param mass the mass of the body on which the force is applied.
*/
Vec& Torque::getAngularAcceleration(double inertia_moment){
	Vec* accel = new Vec(x/inertia_moment, y/inertia_moment, z/inertia_moment);
	return *accel;
}

#endif
