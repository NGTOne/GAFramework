#include "../ApportioningPropagator.hpp"

class AveragingPropagator: public ApportioningPropagator {
	private:

	protected:
	int getAssignableFitness(Individual ** population, int populationSize, Individual * target);

	public:
};
