#ifndef __UNIVERSE_CPP
#define __UNIVERSE_CPP

#include "CtsDynamics.h"

class Universe {
private:
	magnitude time_quantum;
	CollisionDetector cl_detector;
	CollisionHandler cl_handler;
	
public:
	// Creates the universe. It recieves the time quantum or step
	// that will simulate
	Universe(magnitude time_quantum);
	~Universe();
	void simulate();
	void addBody();
	// this is the constant 
	void setTimeQuantum(magnitude quantum);
	void getTimeQuantum() const;
	
};

#endif

