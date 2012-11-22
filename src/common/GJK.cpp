#include "Math.h"
#include "Shape.h"
#include <float.h>
#include <vector>

// SUPER DUPER CODE AFANADOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
typedef std::vector<Vec> Simplex;
typedef std::vector<Vec> ClippedPoints;

struct _simplex_edge {
	double distance;
	size_t index;
	Vec normal;
};

#define TOLERANCE 0.01

Vec support(const Shape& shape1, const Shape& shape2, const Vec& d) {
	Vec nd = !d;
	/* 	d is a Vec direction (doesn't have to be normalized)
	 *	get points on the edge of the shapes in opposite directions
	 *
	 *	Vec p1 = shape1.getFarthestPointInDirection(d);
	 *	Vec p2 = shape2.getFarthestPointInDirection(nd);
	 *
	 *	perform the Minkowski Difference
	 *	(p1-p2) is now a point in Minkowski space on the edge of the Minkowski Difference
	 */
	return (shape1.getFarthestPointInDirection(d)
			- shape2.getFarthestPointInDirection(nd));
}

Vec getDirection(Simplex& s) {
	Vec p;
	return p;
}

bool containsOrigin(Simplex& simplex, Vec& direction) {
// get the last point added to the simplex
	size_t index = simplex.size();
	if (index <= 1) {
		return false;
	}
	Vec a = simplex.back();
// compute AO (same thing as -A)
	Vec ao = !a;
	if (index == 3) {
		const Vec& b = simplex.at(0);
		const Vec& c = simplex.at(1);

		Vec ab = b - a; // vector between a and b
		Vec abPerp = ab.perpendicular2D(); // the perpendicular vector to ab, possibly becomes new search direction if collision is not found
		if (abPerp * c >= 0) { // new direction might "wrong way", check against other side
			abPerp = -abPerp;
		}

		if (abPerp * ao > 0) { // we are in area of direction abPerp
			simplex.erase(simplex.begin() + 1); // remove point in simplex, making it a line

			direction = abPerp; // set a new search direction, where we should look for an new third point
		} else { // we are in area of direction acPerp
			Vec ac = c - a; // sme as for ab and abPerp but between a and c
			Vec acPerp = ac.perpendicular2D();
			if (acPerp * b >= 0) {
				acPerp = -acPerp;
			}

			if (acPerp * ao <= 0) // the origin isn't in the direction of acPerp, we just detected a collision! This is true since we already know that it isn't int the direction of abPerp
				return true; // fast exit

			// does the following only if collision is not found. Erases a point, making the simplex a line and sets a new serach direction in the direction perpendicular to the one between a and c.
			simplex.erase(simplex.begin());
			direction = acPerp;
		}
	} else if (index == 2) { // simplex is a line
		const Vec& b = simplex.at(0);

		// find the vector between the two points
		Vec ab = b - a;

		// find the perpendicular vector in the direction of the origin
		Vec abPerp(-ab.y, ab.x);
		if (abPerp * ao >= 0) {
			abPerp = -abPerp;
		}

		// set direction to the perpendicular vector, this is the direction where we want to look for a third point
		direction = abPerp;
	}

	// no collision this iteration
	return false;
}

bool collide(const Shape& shape1, const Shape& shape2) {
	Vec d(1, 0, 0); // choose a search direction
					// get the first Minkowski Difference point
	Simplex simplex;
	simplex.push_back(support(shape1, shape2, d));
	// negate d for the next point
	Vec nd = !d;
	// start looping
	while (true) {
		// add a new point to the simplex because we haven't terminated yet
		simplex.push_back(support(shape1, shape2, d));
		// make sure that the last point we added actually passed the origin
		if (simplex.back() * d <= 0) {
			// if the point added last was not past the origin in the direction of d
			// then the Minkowski Sum cannot possibly contain the origin since
			// the last point added is on the edge of the Minkowski Difference
			return false;
		} else {
			// otherwise we need to determine if the origin is in
			// the current simplex
			if (containsOrigin(simplex, d)) {
				// if it does then we know there is a collision
				return true;
			}
		}
	}
	return false;
}

_simplex_edge findClosestEdge(const Simplex& s) {

	_simplex_edge closest;
	// prime the distance of the edge to the max
	closest.distance = DBL_MAX;
	// s is the passed in simplex
	size_t index = s.size();
	for (size_t i = 0; i < index; i++) {
		// compute the next points index
		size_t j = i + 1 == index ? 0 : i + 1;
		// get the current point and the next one
		Vec a = s.at(i);
		Vec b = s.at(j);
		// create the edge vector
		Vec e = b - a; // or a.to(b);
		// get the vector from the origin to a
		Vec oa = a; // or a - ORIGIN
		// get the vector from the edge towards the origin
		Vec n = (e ^ oa) ^ e;
		// normalize the vector
		n.normalize();
		// calculate the distance from the origin to the edge
		double d = n * a; // could use b or a here
		// check the distance against the other distances
		if (d < closest.distance) {
			// if this edge is closer then use it
			closest.distance = d;
			closest.normal = n;
			closest.index = j;
		}
	}
	// return the closest edge we found
	return closest;

}

void epa(Shape& shape1, Shape& shape2, Simplex s, Vec& normal, double& depth) {
// loop to find the collision information
	size_t i = 0;
	while (++i < 100) {
		// obtain the feature (edge for 2D) closest to the origin on the Minkowski Difference
		_simplex_edge e = findClosestEdge(s);
		// obtain a new support point in the direction of the edge normal
		Vec p = support(shape1, shape2, e.normal);
		// check the distance from the origin to the edge against the
		// distance p is along e.normal
		double d = (p * e.normal);
		if (d - e.distance < TOLERANCE) {
			// the tolerance should be something positive close to zero (ex. 0.00001)

			// if the difference is less than the tolerance then we can
			// assume that we cannot expand the simplex any further and
			// we have our solution
			Vec normal = e.normal;
			depth = d;
			return;
		} else {
			// we haven't reached the edge of the Minkowski Difference
			// so continue expanding by adding the new point to the simplex
			// in between the points that made the closest edge
			s.insert(s.begin() + e.index, p);
		}
	}
}

// clips the line segment points v1, v2
// if they are past o along n
ClippedPoints clip(const Vec& v1,const Vec& v2,const Vec& n, double o) {
	ClippedPoints cp;
	double d1 = n * v1 - o;
	double d2 = n * v2 - o;
	// if either point is past o along n
	// then we can keep the point
	if (d1 >= 0.0)
		cp.push_back(v1);
	if (d2 >= 0.0)
		cp.push_back(v2);
	// finally we need to check if they
	// are on opposing sides so that we can
	// compute the correct point
	if (d1 * d2 < 0.0) {
		// if they are on different sides of the
		// offset, d1 and d2 will be a (+) * (-)
		// and will yield a (-) and therefore be
		// less than zero
		// get the vector for the edge we are clipping
		Vec e = v2 - v1;
		// compute the location along e
		double u = d1 / (d1 - d2);
		e *= u;
		e += v1;
		// add the point
		cp.push_back(e);
	}
	return cp;
}

ClippedPoints clipping(Shape& shape1, Shape& shape2, Vec& n) {
	Vec nn = !n;
	// find the "best" edge for shape A
	Feature e1 = shape1.getBestFeature(n);
	// find the "best" edge for shape B
	Feature e2 = shape2.getBestFeature(nn);

	if (e1.size() == 1)
		return (ClippedPoints) e1;
	if (e2.size() == 1)
		return (ClippedPoints) e2;

	Edge ref(e1.at(0), e1.at(1)), inc(e2.at(0), e2.at(1));
	bool flip = false;
	Vec maxRef = e1.at(2);
	if (ref.distance() * n > inc.distance() * n) {
		Edge tmp = ref;
		ref = inc;
		inc = tmp;
		maxRef = e2.at(2);
		// we need to set a flag indicating that the reference
		// and incident edge were flipped so that when we do the final
		// clip operation, we use the right edge normal
		flip = true;
	}

	const Vec d = ref.distance();
	Vec ref_normalized = d.normalize();

	double o1 = ref_normalized * ref.v1;
	// clip the incident edge by the first
	// vertex of the reference edge

	Vec nd = !d;
	ClippedPoints cp = clip(inc.v1, inc.v2, d, o1);
	// if we dont have 2 points left then fail
	if (cp.size() < 2)
		return cp;

	// clip whats left of the incident edge by the
	// second vertex of the reference edge
	// but we need to clip in the opposite direction
	// so we flip the direction and offset
	double o2 = d * ref.v2;
	cp = clip(cp.at(0), cp.at(1), nd, -o2);
	// if we dont have 2 points left then fail
	if (cp.size() < 2)
		return cp;

	// get the reference edge normal
	Vec refNorm = ref.distance().perpendicular2D();
	// if we had to flip the incident and reference edges
	// then we need to flip the reference edge normal to
	// clip properly
	if (flip)
		refNorm = !refNorm;
	// get the largest depth
	double max = refNorm * maxRef;
	// make sure the final points are not past this maximum
	if (refNorm * cp.at(0) - max < 0.0) {
		cp.erase(cp.begin());
	}
	if (refNorm * cp.at(1) - max < 0.0) {
		cp.erase(cp.begin() + 1);
	}
	// return the valid points
	return cp;

}
