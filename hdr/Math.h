#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>

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
	Vec operator -();
	Vec operator !();
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
	Vec normalize();
	double norm() const;
	double angle(Vec& b) const;
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

#endif /*MATH_HPP_*/
