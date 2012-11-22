#ifndef __UNIVERSE_CPP
#define __UNIVERSE_CPP

#include "CtsDynamics.h"
//#include "CollisionDetector.h"
//#include "CollisionHandler.h"
#include "Body.h"

#define MAX_BODIES 10

class Universe {
private:
	magnitude time_quantum;
//	CollisionDetector cl_detector;
//	CollisionHandler cl_handler;
	Body** bodies;

public:
	// Creates the universe. It recieves the time quantum or step
	// that will simulate
	Universe(magnitude time_quantum);
	~Universe();
	void simulate();
	void addBody(Body& b);
	// this is the constant 
	void setTimeQuantum(magnitude quantum);
	void getTimeQuantum() const;

};

#endif

