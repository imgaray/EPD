#ifndef POLYGON_H_
#define POLYGON_H_

#include "Shape.h"
#include <iostream>
#include <algorithm>
#include <vector>

#ifndef MAX_POLYGON_VERTICES
#define MAX_POLYGON_VERTICES 10
#endif /* MAX_POLYGON_VERTICES */

class Shape;

class Polygon: public Shape {
public:
	Polygon(Vec& vec);

	virtual void addVertex(Vec& vertex);
	void removeVertes(const Vec& vertex);
	Vec* getVertices() const;
	unsigned short getVerticesCount() const;

	//Shape Interface
	virtual bool contains(const Vec& point) const;
	virtual double getExternalRadius() const;

	//Collisionable Interface
	bool touchesWith(Polygon& p) const;
	bool touchesWith(Circle& c) const;

	//Collider Interface
	bool touches(Collisionable& c) const;

	virtual ~Polygon();

private:
	void recalculateCM();


	Vec* vertices;
	size_t count;
	double max_distance;
};

/*
class ConvexPolygon: public Polygon {
public:
	ConvexPolygon(Vec& vec);
	bool contains(const Vec& point);
	void addVertex(Vec &vertex);

	void setRectangle(double height, double width);

	~ConvexPolygon();
private:
	Vec findFirstVertex();
	void jarvisAlgorithm();

	bool angleComparator(const Vec& center, const Vec& a, const Vec& b);

};
*/
#endif /* POLYGON_H_ */
