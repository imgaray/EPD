#ifndef TORQUE_CPP
#define TORQUE_CPP
#include "Torque.h"

Torque::Torque(double x, double y, double z):Vec(x,y,z){}
Torque::Torque(double x, double y):Vec(x,y,0){}
Torque::Torque():Vec(0,0,0){}
Torque::~Torque(){}

/**
*	Gets the linear acceleration that the force causes to the mass.
*	@param mass the mass of the body on which the force is applied.
*/
Vec& Torque::getAngularAcceleration(double inertia_moment){
	Vec* accel = new Vec(x/inertia, y/inertia, z/inertia);
	return *accel;
}

#endif
