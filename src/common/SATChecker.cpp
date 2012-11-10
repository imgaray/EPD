#include "SATChecker.h"

SATChecker::SATChecker() {
}
SATChecker::~SATChecker() {

}
bool SATChecker::satAlgorithm(Vec* norms, size_t normalsCount,
		Vec* shapeAPoints, Vec* shapeBPoints) {

	return false;
}
bool SATChecker::satAlgorithm(Vec* norms, size_t normalsCount,
		Vec* shapeAPoints, Vec shapeBPosition, double shapeBRadius) {

	for (size_t i = 0; i < normalsCount; i++) {
		Vec max(0), min(0);
		double maxNormA = 0.0, minNormA = 0.0;
		for (size_t j = 0; j < normalsCount; j++) {
			Vec proy = (shapeAPoints[j]).proyected(norms[i]);
			double proyNorm = proy.norm();
			if (j == 0 || proyNorm < minNormA) {
				min = proy;
				minNormA = proyNorm;
			}

			if (j == 0 || proy.norm() > max.norm()) {
				max = proy;
				maxNormA = proyNorm;
			}
		}
		Vec proyC = shapeBPosition.proyected(norms[i]);
		double proyNorm = proyC.norm();
		if ((proyNorm - shapeBRadius > maxNormA) || (proyNorm + shapeBRadius < minNormA))
			return true;
	}

	return false;
}
