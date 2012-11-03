#ifndef POLYGON_CPP
#define POLYGON_CPP

#include "Polygon.h"

Polygon::Polygon() :
		Shape(*(new Vec(0, 0))) {
	this->count = 0;
	this->vertices = new Vec[MAX_POLYGON_VERTICES];
}

Polygon::~Polygon() {

}

void Polygon::addVertex(Vec &point) {
	this->vertices[this->count] = point;
	this->count++;
}

bool Polygon::contains(const Vec& point) {

	return false;
}

#endif /* POLYGON_CPP */
