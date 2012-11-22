#ifndef INTERSECTIONINTERFACE_H_
#define INTERSECTIONINTERFACE_H_

#include "SATChecker.h"

class Touchable;
class Toucher;
class Circle;
class Polygon;

class Toucher{
public:
	virtual bool touches(Touchable& t, Vec* point, Vec* norm, double* penetration,  size_t count) const = 0;
	virtual ~Toucher(){};
};

class Touchable{
public:
	virtual bool touchesWith(Circle& t, Vec* point, Vec* norm, double* penetration,  size_t count) const = 0;
	virtual bool touchesWith(Polygon& p, Vec* point, Vec* norm, double* penetration,  size_t count) const = 0;
	virtual ~Touchable(){};
};

#endif /* INTERSECTIONINTERFACE_H_ */
