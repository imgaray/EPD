#ifndef FLUID_H
#define FLUID_H

#include "../common/Math.hpp"

class Fluid {
private:
	double mass;
	double density;
	double viscosity;

	Force& force;

	double gravity;
public:
	Fluid(double mass, double density);
	virtual ~Fluid();

	double getMass();
	double getDensity();
	double getViscosity();
	double getGravity();

	void setViscosity(double viscosity);
	void setGravity(double gravity);
};

#endif
