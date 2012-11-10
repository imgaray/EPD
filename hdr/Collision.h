#ifndef __COLLISION_H
#define __COLLISION_H

#include "Body.h"

class Collision {
private:
	Body &one, &other;
	bool collided;
public:
	Collision(Body& one, Body& other);
	virtual ~Collision();
}

#endif
