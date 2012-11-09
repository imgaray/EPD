#ifndef CIRCLE_CPP_
#define CIRCLE_CPP_

#include "Circle.h"

//PUBLIC INTERFACE
Circle::Circle(Vec &position_, double radius_) :
		Shape(position_), radius(radius_) {
}

Circle::~Circle() {
}

double Circle::getRadius(){
	return radius;
}

double Circle::getExternalRadius(){
	return radius;
}

// SHAPE INTERFACE
bool Circle::contains(const Vec& point) {
	if (this->center.distance(point).norm() <= this->radius)
		return true;
	return false;
}

// COLLIDER INTERFACE
bool Circle::collide(Collisionable &col) {
	return col.collideWith(*this);
}

// COLLISIONABLE INTERFACE
bool Circle::collideWith(Polygon &p) {
	if ((center.distance(((Shape&) p).getPosition())).norm()
			> (((Shape&) p).getExternalRadius() + radius))
		return false;

	return true;
}

bool Circle::collideWith(Circle &c) {
	return (center.distance(c.center)).norm() <= (radius + c.radius);
}
#endif /*CIRCLE_CPP_*/
