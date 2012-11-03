#include "Circle.h"

Circle::Circle(Vec &position_, double radius_) :
		Shape(position_), radius(radius_) {
}

Circle::~Circle(){}

bool Circle::contains(const Vec& point) {
	if (this->center.distance(point).norm() <= this->radius)
		return true;
	return false;
}

