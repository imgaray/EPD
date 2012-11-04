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
	this->vertices[0].x = 0;
	this->vertices[0].y = height;

	this->vertices[0].x = width;
	this->vertices[0].y = height;

	this->vertices[0].x = width;
	this->vertices[0].y = 0;

	this->vertices[0].x = 0;
	this->vertices[0].y = 0;
}

void ConvexPolygon::addVertex(Vec &point) {
	this->vertices[this->count] = point;
	this->count++;
	try {
		this->jarvisAlgorithm();
		for (unsigned short i = 0; i < this->count; i++) {
			std::cout << vertices[i].x << vertices[i].y << std::endl;
		}
		std::cout << std::endl;
	} catch (char const *str) {
		this->count--;
		throw str;
	}

}

Vec ConvexPolygon::findFirstVertex() {
	Vec min = this->vertices[0];
	for (unsigned short i = 0; i < this->count; i++) {
		if (min != this->vertices[i]) {
			if (this->vertices[i].x < min.x
					|| (this->vertices[i].x == min.x
							&& this->vertices[i].y < min.y))
				min = vertices[i];
		}
	}
	return min;
}

bool ConvexPolygon::angleComparator(const Vec& center, const Vec& a,
		const Vec& b) {
	Vec norm(0, 1);
	Vec centerA = a.distance(center);
	Vec centerB = b.distance(center);
	double angA = norm.angle(centerA);
	double angB = norm.angle(centerB);
	if (centerA.x < 0)
		angA = 2 * M_PI - angA;
	if (centerB.x < 0)
		angB = 2 * M_PI - angB;
	if (angA < angB || (angA == angB && centerA.norm() < centerB.norm()))
		return true;
	return false;
}

/*
 *  ONLY FOR 2D
 *	S: array of vertices
 *	P: array of vertices sorted
 *	pointOnHull = leftmost point in S
 *	i = 0
 *	repeat
 * 		P[i] = pointOnHull
 * 		endpoint = S[0]				// initial endpoint for a candidate edge on the hull
 *		for j from i to |S|-1
 *			if (pointOnHull == endPoint) or (S[j] is on left of line from P[i] to endpoint)
 *				endpoint = S[j]		// found greater left turn, update endpoint
 *		i = i+1
 *		remove endpoint from S
 *		pointOnHull = endpoint
 *	while endpoint != P[0]			// wrapped around to first hull point
 * */
/*
 * TODO: change part of the algorithm to avoid losing the vertex if the polygon is not convex.
 * */
void ConvexPolygon::jarvisAlgorithm() {
	Vec* order = new Vec[MAX_POLYGON_VERTICES];
	Vec pointOnHull = findFirstVertex();
	Vec endPoint = this->vertices[0];
	unsigned short i = 0, j = 0, lastVertex = 0;
	do {
		order[i] = pointOnHull;
		endPoint = this->vertices[0];

		for (j = i; j < this->count; j++) {
			if (pointOnHull == endPoint
					|| (this->vertices[j] != pointOnHull
							&& angleComparator(pointOnHull, this->vertices[j],
									endPoint))) {
				endPoint = this->vertices[j];
				lastVertex = j;
			}
		}
		i++;
		vertices[lastVertex] = vertices[i];
		pointOnHull = endPoint;
	} while (pointOnHull != order[0]);

	delete[] this->vertices;

	if (i != this->count)
		throw "Not a convex polygon";
	else
		this->vertices = order;
}

/*
 * THE MAGIC, only works in 2D
 * */
bool ConvexPolygon::contains(const Vec& point) {
	for (unsigned short i = 0; i < this->count - 1; i++) {
		if (point == vertices[i])
			return true;
		if (((vertices[i + 1] - vertices[i]).cross(vertices[i].distance(point))).z
				< 0.0)
			return false;
	}
	if (point == vertices[this->count - 1])
		return true;
	if (((vertices[0] - vertices[this->count - 1]).cross(
			vertices[this->count - 1].distance(point))).z >= 0.0)
		return true;
	return false;
}

#endif /* POLYGON_CPP */
