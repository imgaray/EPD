#ifndef INTERSECTIONINTERFACE_H_
#define INTERSECTIONINTERFACE_H_

#include "SATChecker.h"

class Touchable;
class Toucher;
class Circle;
class Polygon;

class Toucher{
public:
	virtual bool touches(Touchable& t, Vec& point, Vec& norm) const = 0;
	virtual ~Toucher(){};
};

class Touchable{
public:
	virtual bool touchesWith(Circle& t) const = 0;
	virtual bool touchesWith(Polygon& p) const = 0;
	virtual ~Touchable(){};
};

#endif /* INTERSECTIONINTERFACE_H_ */
