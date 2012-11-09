#ifndef CICLE_H_
#define CICLE_H_

#include "Shape.h"

class Shape;

class Circle: public Shape{
public:
	Circle(Vec& position, double radius);
	~Circle();
	double getRadius();


	//Shape Interface
	virtual bool contains(const Vec& point);
	double getExternalRadius();

	//Collisionable Interface
	bool collideWith(Polygon& p);
	bool collideWith(Circle& p);

	//Collider Interface
	bool collide(Collisionable& p);

private:
	double radius;
};



#endif /* CICLE_H_ */
