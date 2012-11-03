#ifndef POLYGON_CPP
#define POLYGON_CPP

#include "Polygon.h"

// POLYGON //
Polygon::Polygon(Vec& vec) :
		Shape(vec) {
	this->count = 0;
	this->vertices = new Vec[MAX_POLYGON_VERTICES];
	this->normals = new Vec[MAX_POLYGON_VERTICES];
}

Polygon::~Polygon() {
	delete[] this->vertices;
	delete[] this->normals;
}

Vec* Polygon::getVertices() {
	return this->vertices;
}

unsigned short Polygon::getVerticesCount() {
	return this->count;
}
////////////////////
// CONVEX POLYGON //

ConvexPolygon::ConvexPolygon(Vec& vec) :
		Polygon(vec) {
}

ConvexPolygon::~ConvexPolygon() {
}

void ConvexPolygon::setRectangle(double height, double width) {

}

void ConvexPolygon::addVertex(Vec &point) {
	this->vertices[this->count] = point;
	this->count++;
}

bool ConvexPolygon::contains(const Vec& point) {

	return false;
}
#endif /* POLYGON_CPP */
