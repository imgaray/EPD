#ifndef FLUID_CPP
#define FLUID_CPP
#include "Fluid.h"

Fluid::Fluid(double mass, double density, double viscosity): force(*(new Force())){
	this->mass = mass;
	this->density = density;
	this->viscosity = viscosity;
	this->gravity = 0;
}
Fluid::~Fluid(){}	

double Fluid::getMass(){
	return 0;
}
double Fluid::getDensity(){
	return 0;
}
double Fluid::getViscosity(){
	return 0;
}
double Fluid::getGravity(){
	return 0;
}

void Fluid::setViscosity(double viscosity){}
void Fluid::setGravity(double gravity){}
#endif
