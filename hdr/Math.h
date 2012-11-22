#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>
#include <vector>

class Vec {
public:
	double x, y, z;
	Vec(double x = 0, double y = 0, double z = 0);
	Vec(const Vec& other);
	/* redefinition methods*/
	void operator +=(const Vec& v);
	void operator -=(const Vec& v);
	void operator *=(double k);
	void operator /=(double k);
	Vec operator -() const;
	Vec operator !() const;
	bool operator ==(const Vec& a) const;
	bool operator !=(const Vec& a) const;
	Vec operator +(const Vec& a) const;
	Vec operator -(const Vec& a) const;
	Vec operator *(double k) const;
	Vec operator /(double k) const;
	double operator *(const Vec& a) const;
	Vec operator ^(const Vec& a) const;

	Vec& operator=(const Vec& v);

	/* methods*/
	void set(double x, double y, double z);
	Vec normalize() const;
	Vec rotateXY(double radians) const;
	double norm() const;
	double angle(const Vec& b) const;
	Vec distance(const Vec& a) const;
	Vec proyected(const Vec& a) const;
	double dot(const Vec& a) const;
	Vec cross(const Vec& a) const;

	/* coordenate changes */
	// convention: (radius, phi, theta)
	// radius >= 0
	// 0 <= phi < pi
	// 0 <= theta < 2pi
	Vec toSphericals() const;
	// convention: (radius, theta, z)
	// radius >= 0
	// 0 <= theta < 2pi
	// z is the same as in canonical base	
	Vec toCylindrical() const;

	// TODO(nacho): see if implement this.
	Vec toCanonicalFromSph() const;
	Vec toCanonicalFromCyl() const;

	Vec perpendicular2D() const;
	virtual ~Vec();

};

class Edge {
public:
	Vec v1, v2;
	Edge(Vec& v1, Vec& v2);
	Edge(const Edge& other);
	Edge(Vec& v1);

	Vec distance();
	~Edge();
};

typedef std::vector<Vec> Feature;

#endif /*MATH_HPP_*/
