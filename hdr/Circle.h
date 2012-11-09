#ifndef CICLE_H_
#define CICLE_H_

#include "Shape.h"

class Circle;

class Circle: public Shape{
public:
	Circle(Vec& position, double radius);
	~Circle();
	double getRadius() const;


	//Shape Interface
	virtual bool contains(const Vec& point) const;
	double getExternalRadius() const;

	//Collisionable Interface
	bool touchesWith(Polygon& p) const;
	bool touchesWith(Circle& c) const;

	//Collider Interface
	bool touches(Touchable& c) const;

private:
	double radius;
};



#endif /* CICLE_H_ */
