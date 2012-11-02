#ifndef MATH_CPP
#define MATH_CPP

#include "Math.h"


/** 
	Constructor 3 dimensional vector.
	@param x first coordinate of the vector.
	@param y second coordinate of the vector.
	@param z third coordinate of the vector.
*/
Vec::Vec(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

/** 
	Constructor 3 dimensional vector, z = 0.
	@param x first coordinate of the vector.
	@param y second coordinate of the vector.
*/
Vec::Vec(double x, double y){
	this->x = x;
	this->y = y;
	this->z = 0;
}

/** 
	Destructor of vector.
*/
Vec::~Vec(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


void Vec::operator += (const Vec& v){
	this->x += v.x;	this->y += v.y;	this->z += v.z;
}

void Vec::operator -= (const Vec& v){
	this->x -= v.x;	this->y -= v.y;	this->z -= v.z;
}

void Vec::operator *= (double k){
	this->x *= k;	this->y *= k;	this->z *= k;
}
void Vec::operator /= (double k){
	this->x /= k;	this->y /= k;	this->z /= k;
}

/*
double Vec::operator () (int i){
	switch(){
		case 1:
			return x;break;
		case 2:
			return y;break;
		case 3:
			return z;break;
	}
}
*/

Vec Vec::operator -(){
	Vec v(this->x * -1, this->y *-1, this->z * -1);
	return v;
}

Vec Vec::operator !(){
	Vec v(this->x * -1, this->y *-1, this->z * -1);
	return v;
}

bool Vec::operator == (const Vec& a){
	return (x == a.x && y == a.y && z == a.y);
}

Vec Vec::operator + (const Vec& a){
	Vec v(this->x + a.x, this->y + a.y, this->z + a.z);
	return v;
}

Vec Vec::operator - (const Vec& a){
	Vec v(this->x - a.x, this->y - a.y, this->z - a.z);
	return v;
}

Vec Vec::operator * (double k){
	Vec v(this->x * k, this->y * k, this->z * k);
	return v;
}

Vec Vec::operator / (double k){
	Vec v(this->x / k, this->y / k, this->z / k);
	return v;
}

Vec Vec::normalize(){
	Vec v(0,0,0);
	double n = this->norm();
	if (n)
		v.set(x/n, y/n, z/n);
	return v;
}

double Vec::norm(){
	return sqrt(x*x+y*y+z*z);
}

Vec Vec::distance(const Vec& a){
	Vec v(this->x - a.x, this->y - a.y, this->z - a.z);
	return v;
}

void Vec::set(double x, double y, double z){
	this->x = x; this->y = y; this->z = z;
}

Vec Vec::dot(const Vec& a){
	Vec v(this->x * a.x, this->y * a.y, this->z *a.z);
	return v;
}

Vec Vec::cross(const Vec& a){
	Vec v(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
	return v;
}

#endif /* MATH_CPP*/
