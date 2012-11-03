#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>

class Vec{
	public:
		double x, y, z;
		Vec(double x, double y, double z);
		Vec(double x, double y);
		Vec();
		/* redefinition methods*/
		void operator += (const Vec& v);
        void operator -= (const Vec& v);
        void operator *= (double k);
		void operator /= (double k);
		Vec operator -();
		Vec operator !();
		bool operator == (const Vec& a);
		Vec operator + (const Vec& a);
		Vec operator - (const Vec& a);
		Vec operator * (double k);
		Vec operator / (double k);

		/* methods*/
		void set(double x, double y, double z); 			
		Vec normalize();
		double norm() const;
		Vec distance(const Vec& a) const;
		Vec dot(const Vec& a) const;
		Vec cross(const Vec& a) const;
		
		virtual ~Vec();	

};

#endif /*MATH_HPP_*/
