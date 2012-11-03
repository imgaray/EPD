#ifndef TORQUE_H
#define TORQUE_H

#include "Math.h"

class Torque: public Vec {
public:
	Torque(double x = 0, double y = 0, double z = 0);

	Vec& getAngularAcceleration(double inertia_moment);
	virtual ~Torque();
};

#endif
