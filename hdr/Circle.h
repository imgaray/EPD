#ifndef CICLE_H_
#define CICLE_H_

#include "Shape.h"

class Circle;

class Circle: public Shape {
public:
	Circle(Vec& position, double radius);
	~Circle();
	double getRadius() const;

	//Shape Interface
	virtual bool contains(const Vec& point) const;
	double getExternalRadius() const;
	Vec getFarthestPointInDirection(const Vec& direction) const;
	Feature getBestFeature(Vec& direction) const;

	//Collisionable Interface
	bool touchesWith(Polygon& p, Vec* point, Vec* norm, double* penetration,
			size_t count) const;
	bool touchesWith(Circle& c, Vec* point, Vec* norm, double* penetration,
			size_t count) const;

	//Collider Interface
	bool touches(Touchable& c, Vec* point, Vec* norm, double* penetration,
			size_t count) const;

private:
	double radius;
};

#endif /* CICLE_H_ */
