#ifndef TORQUE_H
#define TORQUE_H

#include "../common/Math.hpp"

class Torque: public Vec{
public:
	Torque(double x, double y, double z);
	Torque(double x, double y);
	Torque();

	Vec& getAngularAcceleration(double inertia_moment);
	virtual ~Torque();
};


#endif
