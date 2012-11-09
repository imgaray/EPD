#ifndef SHAPE_CPP
#define SHAPE_CPP
#include "Shape.h"

Shape::Shape(Vec& pos):center(pos){}
Shape::~Shape(){}

Vec Shape::getPosition(){
	return center;
}
#endif /* SHAPE_CPP */
