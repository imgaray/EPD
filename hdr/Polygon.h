#ifndef POLYGON_H_
#define POLYGON_H_

#include "Shape.h"
#include <iostream>
#include <algorithm>
#include <vector>

#ifndef MAX_POLYGON_VERTICES
#define MAX_POLYGON_VERTICES 10
#endif /* MAX_POLYGON_VERTICES */

class Circle;

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
	virtual Vec getFarthestPointInDirection(const Vec& direction) const;
	virtual Feature getBestFeature(Vec& direction) const;

	//Touchable Interface
	bool touchesWith(Polygon& p, Vec* point, Vec* norm, double* penetration,
			size_t count) const;
	bool touchesWith(Circle& c, Vec* point, Vec* norm, double* penetration,
			size_t count) const;

	//Toucher Interface
	bool touches(Touchable& c, Vec* point, Vec* norm, double* penetration,
			size_t count) const;

	virtual ~Polygon();

private:
	void recalculateCM();
	void recalculateNorms();
	size_t getFarthestVertexIndexInDirection(const Vec& direction) const;
	Vec* vertices, *norms;
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
