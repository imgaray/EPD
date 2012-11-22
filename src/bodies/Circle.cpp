#ifndef CIRCLE_CPP_
#define CIRCLE_CPP_

#include "Circle.h"

//PUBLIC INTERFACE
Circle::Circle(Vec &position_, double radius_) :
		Shape(position_), radius(radius_) {
}

Circle::~Circle() {
}

double Circle::getRadius() const {
	return radius;
}

double Circle::getExternalRadius() const {
	return radius;
}

// SHAPE INTERFACE
bool Circle::contains(const Vec& point) const {
	if (this->center.distance(point).norm() <= this->radius)
		return true;
	return false;
}

Vec Circle::getFarthestPointInDirection(const Vec& direction) const {
	Vec farthestPoint = center;
	Vec rad(radius, 0);
	double angle = rad.angle(direction);
	if (direction.y < 0)
		return rad.rotateXY(M_PI - angle);
	return rad.rotateXY(angle);
}

Feature Circle::getBestFeature(Vec& direction) const {
	Feature f;
	f.push_back(getFarthestPointInDirection(direction));
	return f;
}
// COLLIDER INTERFACE
bool Circle::touches(Touchable &col, Vec* point, Vec* norm,
		double* penetrations, size_t count) const {
	return col.touchesWith((Circle&) *this, point, norm, penetrations, count);
}

// COLLISIONABLE INTERFACE
bool Circle::touchesWith(Polygon &p, Vec* point, Vec* norm, double* penetration,
		size_t count) const {
	if ((center.distance(((Shape&) p).getPosition())).norm()
			> (((Shape&) p).getExternalRadius() + radius))
		return false;
	return true;
}

bool Circle::touchesWith(Circle &c, Vec* point, Vec* norm, double* penetration,
		size_t count) const {
	if ((center.distance(c.center)).norm() <= (radius + c.radius)) {
		norm[0] = (center - c.center).normalize();
		point[0] = center + norm[0] * radius;
		return true;
	}
	return false;
}
#endif /*CIRCLE_CPP_*/
