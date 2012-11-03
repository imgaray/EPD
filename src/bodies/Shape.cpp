#ifndef SHAPE_CPP
#define SHAPE_CPP
#include "Shape.h"

Shape::Shape(Vec& pos):center(pos){}

Shape::~Shape(){
	delete &(this->center);
}


#endif /* SHAPE_CPP */
