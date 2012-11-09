#ifndef INTERSECTIONINTERFACE_H_
#define INTERSECTIONINTERFACE_H_

class Touchable;
class Toucher;
class Circle;
class Polygon;

class Toucher{
public:
	virtual bool touches(Touchable& t) const = 0;
	virtual ~Toucher(){};
};

class Touchable{
public:
	virtual bool touchesWith(Circle& t) const = 0;
	virtual bool touchesWith(Polygon& p) const = 0;
	virtual ~Touchable(){};
};

#endif /* INTERSECTIONINTERFACE_H_ */
