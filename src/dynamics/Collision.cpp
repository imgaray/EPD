#include "Collision.h"

Collision::Collision(Body& one, Body& other) :
		one(one), other(other), collided(false) {
}

Collision::~Collision() {
}
