#ifndef SHAPE_H_
#define SHAPE_H_

#include "Math.h"
#include "IntersectionInterface.h"

class Shape: public Toucher, public Touchable{
public:
	virtual bool contains(const Vec& point) const = 0;
	virtual ~Shape() = 0;
	Shape(Vec& position);
	Vec getPosition();
	virtual double getExternalRadius() const = 0;

protected:
	Vec& center;
};

#endif /* SHAPE_H_ */
