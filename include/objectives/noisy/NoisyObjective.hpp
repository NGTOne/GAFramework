#include "../../core/NestedObjective.hpp"
#include <random>

class NoisyObjective: public NestedObjective {
	private:

	protected:
	std::mt19937 generator;

	virtual float addNoise(float cleanFitness)=0;

	public:
	NoisyObjective(ObjectiveFunction * cleanObjective);
	NoisyObjective(ObjectiveFunction * cleanObjective, unsigned int seed);
	float checkFitness(Genome * genome);
};
