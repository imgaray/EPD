#ifndef SHAPE_H_
#define SHAPE_H_

#include "../common/Math.h"

class Shape{
public:
	virtual bool contains(const Vec& point)= 0;
	virtual ~Shape() = 0;
	Shape(Vec& position);
protected:
	Vec center;
};

#endif /* SHAPE_H_ */
