#ifndef SHAPE_H_
#define SHAPE_H_

#include "Math.h"
#include "CollisionInterface.h"

class Shape: public Collider, public Collisionable{
public:
	virtual bool touches(const Shape& other) = 0;
	virtual bool contains(const Vec& point) = 0;
	virtual ~Shape() = 0;
	Shape(Vec& position);
	Vec getPosition();
	virtual double getExternalRadius() = 0;

protected:
	Vec& center;
};

#endif /* SHAPE_H_ */
