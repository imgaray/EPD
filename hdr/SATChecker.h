#ifndef SATCHECKER_H_
#define SATCHECKER_H_

#include "Math.h"
#include <stdlib.h>

class SATChecker {
public:
	SATChecker();
	~SATChecker();
	bool satAlgorithm(Vec* norms, size_t normalsCount, Vec* shapeAPoints, Vec* shapeBPoints);
	bool satAlgorithm(Vec* norms, size_t normalsCount, Vec* shapeAPoints, Vec shapeBPosition, double shapeBRadius);
};


#endif /* SATCHECKER_H_ */
