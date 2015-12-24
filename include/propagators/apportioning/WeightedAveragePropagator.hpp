#include "../ApportioningPropagator.hpp"

class WeightedAveragePropagator: public ApportioningPropagator {
	private:

	protected:
	int getAssignableFitness(
		Individual ** population,
		int populationSize,
		Individual * target
	);

	public:
};
