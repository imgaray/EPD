#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Math.h"

class Transform2D {
private:
	Vec tslate;
	Vec rowA, rowB;
	double rad;
public:
	Transform2D(const Vec& pos = Vec(), double rad = 0.);
	Transform2D(const Transform2D& other);
	Transform2D& operator=(const Transform2D& v);

	~Transform2D();
	void translate(const Vec& a);
	void rotate(double radians);
	void reset();
	Vec transform(const Vec& point);
};

#endif /* TRANSFORM_H_ */
