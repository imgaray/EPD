#ifndef FORCE_H
#define FORCE_H

#include "../common/Math.h"
#include "Torque.h"

class Force: public Vec{
public:
	Force(double x = 0, double y = 0, double z = 0);

	Vec& getLinearAcceleration(double mass);
	Torque& getToque(const Vec& point) const;
	virtual ~Force();
};


#endif
