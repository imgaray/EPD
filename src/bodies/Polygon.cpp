#ifndef POLYGON_CPP
#define POLYGON_CPP

#include "Polygon.h"

// PUBLIC INTERFACE POLYGON //
Polygon::Polygon(Vec& vec) :
		Shape(vec) {
	this->count = 1;
	this->vertices = new Vec[MAX_POLYGON_VERTICES];
	this->norms = new Vec[MAX_POLYGON_VERTICES];
	this->vertices[0] = vec;
}

Polygon::~Polygon() {
	delete[] this->vertices;
	delete[] this->norms;
}

void Polygon::addVertex(Vec& vertex) {
	if (this->count < MAX_POLYGON_VERTICES)
		this->vertices[this->count++] = vertex;
	recalculateCM();
	recalculateNorms();
}

void Polygon::removeVertes(const Vec& vertex) {
	bool foundVertex = false;
	for (unsigned short i = 0; i < this->count; i++) {
		if (this->vertices[i] == vertex)
			foundVertex = true;
		if (foundVertex && i < this->count - 1)
			this->vertices[i] = this->vertices[i + 1];
	}
}

Vec* Polygon::getVertices() const {
	return this->vertices;
}

unsigned short Polygon::getVerticesCount() const {
	return this->count;
}

double Polygon::getExternalRadius() const {
	return this->max_distance;
}

// PROTECTED INTERFACE
void Polygon::recalculateCM() {
	double area = 0;
	Vec nC;
	for (size_t i = 0; i < count - 1; i++) {
		nC += ((vertices[i] + vertices[i + 1])
				* (vertices[i].x * vertices[i + 1].y
						- vertices[i].y * vertices[i + 1].x));
		area += (vertices[i].x * vertices[i + 1].y
				- vertices[i].y * vertices[i + 1].x);
	}
	area /= 2;
	center = nC / (6 * area);
	for (size_t i = 0; i < count - 1; i++) {
		double norm = (vertices[i] - center).norm();
		if (norm > max_distance)
			max_distance = norm;
	}
}

void Polygon::recalculateNorms() {
	for (size_t i = 0; i < count; i++) {
		Vec v2 = vertices[0];
		if (i < count - 1)
			v2 = vertices[i + 1];
		norms[i] = (v2 - vertices[i]).perpendicular2D();
	}
}

// SHAPE INTERFACE
bool Polygon::contains(const Vec& point) const {
	unsigned short count = 0;
	for (unsigned short i = 0; i < this->count; i++) {
		Vec v1 = this->vertices[i], v2 = this->vertices[0];
		if (i < this->count - 1)
			v2 = vertices[i + 1];
		double minX = std::min(v1.x, v2.x);
		double maxX = std::max(v1.x, v2.x);
		if (minX <= point.x && maxX >= point.x && minX != maxX) {
			double k2 = (point.x - v2.x) / (v2.x - v1.x);
			double k = (k2 * (v2.y - v1.y) + v2.y) / point.y;
			if (k == 1.0)
				return true;
			if (k > 1.0)
				count++;
		} else if (minX == maxX && minX == point.x) {
			double minY = std::min(v1.y, v2.y);
			double maxY = std::max(v1.y, v2.y);
			if (minY <= point.y && maxY >= point.y) {
				return true;
			}
		}
	}
	return (count % 2 != 0);
}

// COLLIDER INTERFACE
bool Polygon::touches(Touchable &col) const {
	return col.touchesWith((Polygon&) *this);
}

// COLLISIONABLE INTERFACE
bool Polygon::touchesWith(Polygon &p) const {
	if ((center.distance(p.center)).norm() > (max_distance + p.max_distance))
		return false;

	for (size_t i = 0; i < p.count; i++) {
		if (this->contains(p.vertices[i]))
			return true;
	}

	for (size_t i = 0; i < count; i++) {
		if (p.contains(vertices[i]))
			return true;
	}
	return false;
}

bool Polygon::touchesWith(Circle &circle) const {
	Shape& s = ((Shape&) circle);
	if ((center.distance(s.getPosition())).norm()
			> (max_distance + s.getExternalRadius()))
		return false;

	Vec* normsToCheck = new Vec[this->count + 1];

	double minDistanceAxis = 0.0;
	Vec normC(0);
	for (size_t i = 0; i < this->count; i++) {
		normsToCheck[i] = norms[i];
		Vec potentialAxis = s.getPosition() - vertices[i];
		double norm = potentialAxis.norm();
		if (i == 0 || norm < minDistanceAxis) {
			minDistanceAxis = norm;
			normC = potentialAxis.perpendicular2D();
		}
	};

	normsToCheck[count] = normC;
	bool ans = SATChecker().satAlgorithm(normsToCheck, count + 1, vertices,
			s.getPosition(), s.getExternalRadius());
	delete[] normsToCheck;
	return ans;
}

/*
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

 void ConvexPolygon::addVertex(Vec &vertex) {
 if (this->count < MAX_POLYGON_VERTICES) {
 this->vertices[this->count++] = vertex;
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
 */
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
/*void ConvexPolygon::jarvisAlgorithm() {
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
 */
/*
 * THE MAGIC, only works in 2D
 * */
/*bool ConvexPolygon::contains(const Vec& point) {
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
 */
#endif /* POLYGON_CPP */
