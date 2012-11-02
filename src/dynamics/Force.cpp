#ifndef FORCE_CPP
#define FORCE_CPP
#include "Force.h"

Force::Force(double x, double y, double z):Vec(x,y,z){
}
Force::Force(double x, double y):Vec(x,y,0){
}
Force::Force():Vec(0,0,0){
}
Force::~Force(){}

/**
*	Gets the linear acceleration that the force causes to the mass.
*	@param mass the mass of the body on which the force is applied.
*/
Vec& Force::getLinearAcceleration(double mass){
	Vec* accel = new Vec(x/mass, y/mass, z/mass);
	return *accel;
}

/**
*	Gets the torque, product of the force applied in a particular point.
*	@param mass the mass of the body on which the force is applied.
*/
Torque& Force::getToque(Vec& point){
	Vec v = point.cross((Vec&)*this);
	Torque* torque = new Torque(v.x, v.y, v.z);
	return *torque;
}

#endif
