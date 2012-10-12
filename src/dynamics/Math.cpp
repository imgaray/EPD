#include "Math.hpp"

Vec::Vec(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec::Vec(double x, double y){
	this->x = x;
	this->y = y;
	this->z = 0;
}
