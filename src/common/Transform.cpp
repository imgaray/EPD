#ifndef TRANSFORM_CPP
#define TRANSFORM_CPP
#include "Transform.h"

Transform2D::Transform2D(const Vec& pos, double rad) :
		tslate(), rowA(), rowB() {
	translate(pos);
	rotate(rad);
}

Transform2D::Transform2D(const Transform2D& other) :
		tslate(other.tslate), rowA(other.rowA), rowB(other.rowB) {
	rotate(other.rad);
}

Transform2D& Transform2D::operator=(const Transform2D& t) {
	tslate = t.tslate;
	rowA = t.rowA;
	rowB = t.rowB;
	rad = t.rad;
	return (*this);
}

Transform2D::~Transform2D() {

}

void Transform2D::translate(const Vec& a) {
	this->tslate += a;
}

void Transform2D::rotate(double radians) {
	this->rad += radians;
	double cosRad = cos(radians);
	double sinRad = sin(radians);
	rowA.set(cosRad, sinRad, 0);
	rowB.set(-sinRad, cosRad, 0);
}

void Transform2D::reset() {
	tslate.set(0, 0, 0);
	rad = 0;
	rowA.set(0, 0, 0);
	rowB.set(0, 0, 0);
}

Vec Transform2D::transform(const Vec& p) {
	// rowA.set(rowA.x, rowA.y, rowA * tslate);
	rowA.z = rowA * tslate;
	//rowB.set(rowB.x, rowB.y, rowB * tslate);
	rowB.z = rowA * tslate;
	return Vec(rowA * p, rowB * p, 0);
}

#endif /* TRANSFORM_CPP*/
