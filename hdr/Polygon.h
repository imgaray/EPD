#ifndef POLYGON_H_
#define POLYGON_H_

#include "Shape.h"

#ifndef MAX_POLYGON_VERTICES
#define MAX_POLYGON_VERTICES 10
#endif /* MAX_POLYGON_VERTICES */

class Polygon: public Shape {
public:
	Polygon(Vec& vec);
	bool contains(const Vec& point) = 0;

	Vec* getVertices();
	unsigned short getVerticesCount();

	virtual ~Polygon();
protected:
	Vec* vertices;
	Vec* normals;
	short count;

};

class ConvexPolygon: public Polygon {
public:
	ConvexPolygon(Vec& vec);
	bool contains(const Vec& point);
	void addVertex(Vec &vertex);

	void setRectangle(double height, double width);

	~ConvexPolygon();
private:
};

#endif /* POLYGON_H_ */
