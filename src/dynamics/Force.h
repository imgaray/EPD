#ifndef FORCE_H
#define FORCE_H

#include "../common/Math.h"
#include "Torque.h"

class Force: public Vec{
public:
	Force(double x, double y, double z);
	Force(double x, double y);
	Force();

	Vec& getLinearAcceleration(double mass);
	Torque& getToque(Vec& point);
	virtual ~Force();
};


#endif
