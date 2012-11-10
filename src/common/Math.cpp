#ifndef MATH_CPP
#define MATH_CPP

#include "Math.h"

/** 
 *	Constructor 3 dimensional vector.
 *	@param x first coordinate of the vector.
 *	@param y second coordinate of the vector.
 *	@param z third coordinate of the vector.
 */
Vec::Vec(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

/** 
 *	Destructor of vector.
 */
Vec::~Vec() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec& Vec::operator=(const Vec& v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return (*this);
}

Vec::Vec(const Vec& other) :
		x(other.x), y(other.y), z(other.z) {
}

void Vec::operator +=(const Vec& v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vec::operator -=(const Vec& v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void Vec::operator *=(double k) {
	this->x *= k;
	this->y *= k;
	this->z *= k;
}
void Vec::operator /=(double k) {
	this->x /= k;
	this->y /= k;
	this->z /= k;
}

/*
 *double Vec::operator () (int i){
 *	switch(){
 *		case 1:
 *			return x;break;
 *		case 2:
 *			return y;break;
 *		case 3:
 *			return z;break;
 *	}
 *}
 */

Vec Vec::operator -() {
	Vec v(this->x * -1, this->y * -1, this->z * -1);
	return v;
}

Vec Vec::operator !() {
	Vec v(this->x * -1, this->y * -1, this->z * -1);
	return v;
}

bool Vec::operator ==(const Vec& a) const {
	return (x == a.x && y == a.y && z == a.z);
}

bool Vec::operator !=(const Vec& a) const {
	return !(*this == a);
}

Vec Vec::operator +(const Vec& a) const {
	Vec v(this->x + a.x, this->y + a.y, this->z + a.z);
	return v;
}

Vec Vec::operator -(const Vec& a) const {
	Vec v(this->x - a.x, this->y - a.y, this->z - a.z);
	return v;
}

Vec Vec::operator *(double k) const {
	Vec v(this->x * k, this->y * k, this->z * k);
	return v;
}

Vec Vec::operator /(double k) const {
	Vec v(this->x / k, this->y / k, this->z / k);
	return v;
}

double Vec::operator *(const Vec& a) const {
	return this->dot(a);
}
Vec Vec::operator ^(const Vec& a) const {
	return this->cross(a);
}

Vec Vec::normalize() {
	Vec v(0, 0, 0);
	double n = this->norm();
	if (n)
		v.set(x / n, y / n, z / n);
	return v;
}

Vec Vec::perpendicular2D() const {
	Vec v(y, -x);
	return v;
}

double Vec::norm() const {
	return sqrt(x * x + y * y + z * z);
}

double Vec::angle(Vec& a) const {
	return acos(this->dot(a) / (this->norm() * a.norm()));
}

Vec Vec::distance(const Vec& a) const {
	Vec v(this->x - a.x, this->y - a.y, this->z - a.z);
	return v;
}

void Vec::set(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec Vec::proyected(const Vec& b) const {
	double dotAB = (*this) * b;
	double dotB = b * b;
	return (*this) * dotAB / dotB;
}

double Vec::dot(const Vec& a) const {
	return this->x * a.x + this->y * a.y + this->z * a.z;
}

Vec Vec::cross(const Vec& a) const {
	Vec v(0, 0, x * a.y - y * a.x);
	if (z == 0.0 && a.z == 0.0)
		return v;
	Vec v2(y * a.z - z * a.y, z * a.x - x * a.z, 0);
	return v + v2;
}

#endif /* MATH_CPP*/
