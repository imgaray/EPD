#ifndef FORCE_CPP
#define FORCE_CPP
#include "Force.h"

Force::Force(double x, double y, double z) :
		Vec(x, y, z) {
}

Force::Force(const Vec& vec) :
		Vec(vec) {
}

Force::Force(const Force& other) :
		Vec((Vec&) other) {
}

// by convention, (radius, phi, theta)
Force Force::toSpherical() const {
	return Force(this->toSphericals());
}

Force Force::toCylindrical() const {
	return Force(this->toCylindrical());
}

Force::~Force() {
}

/**
 *	Gets the linear acceleration that the force causes to the mass.
 *	@param mass the mass of the body on which the force is applied.
 */
Vec Force::getLinearAcceleration(double mass) {
	return Vec(x / mass, y / mass, z / mass);
}

/**
 *	Gets the torque, product of the force applied in a particular point.
 *	@param mass the mass of the body on which the force is applied.
 */
Torque Force::getToque(const Vec& point) const {
	return Torque(point ^ ((Vec&) *this));
}

#endif
