#ifndef FORCE_H
#define FORCE_H

#include "Math.h"
#include "Torque.h"

class Force: public Vec{
private:
	Force(const Vec& vector);
public:
	Force(double x = 0, double y = 0, double z = 0);
	Force(const Force& vector);

	Vec getLinearAcceleration(double mass);
	Torque getToque(const Vec& point) const;
	Force toCylindrical() const;
	Force toSpherical() const;
	virtual ~Force();
};


#endif
