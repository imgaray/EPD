#ifndef CICLE_H_
#define CICLE_H_

#include "Shape.h"

class Circle: public Shape{
public:
	Circle(Vec& position, double radius);
	bool contains(const Vec& point);
	~Circle();
private:
	double radius;
};



#endif /* CICLE_H_ */
