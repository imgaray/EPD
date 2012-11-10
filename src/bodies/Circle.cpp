#ifndef CIRCLE_CPP_
#define CIRCLE_CPP_

#include "Circle.h"

//PUBLIC INTERFACE
Circle::Circle(Vec &position_, double radius_) :
		Shape(position_), radius(radius_) {
}

Circle::~Circle() {
}

double Circle::getRadius() const{
	return radius;
}

double Circle::getExternalRadius() const{
	return radius;
}

// SHAPE INTERFACE
bool Circle::contains(const Vec& point) const{
	if (this->center.distance(point).norm() <= this->radius)
		return true;
	return false;
}

// COLLIDER INTERFACE
bool Circle::touches(Touchable &col) const{
	return col.touchesWith((Circle&)*this);
}

// COLLISIONABLE INTERFACE
bool Circle::touchesWith(Polygon &p) const{
	if ((center.distance(((Shape&) p).getPosition())).norm()
			> (((Shape&) p).getExternalRadius() + radius))
		return false;

	return true;
}

bool Circle::touchesWith(Circle &c) const{
	return (center.distance(c.center)).norm() <= (radius + c.radius);
}
#endif /*CIRCLE_CPP_*/
