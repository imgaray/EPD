#ifndef POLYGON_H_
#define POLYGON_H_

#include "Shape.h"

#ifndef MAX_POLYGON_VERTICES
#define MAX_POLYGON_VERTICES 10
#endif /* MAX_POLYGON_VERTICES */

class Polygon: public Shape {
public:
	Polygon();
	bool contains(const Vec& point);
	void addVertex(Vec &point);
	~Polygon();
private:
	Vec* vertices;
	short count;
};

#endif /* POLYGON_H_ */
