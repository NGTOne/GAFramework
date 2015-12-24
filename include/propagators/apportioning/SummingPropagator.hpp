#include "../ApportioningPropagator.hpp"

class SummingPropagator: public ApportioningPropagator {
	private:

	protected:
	int getAssignableFitness(
		Individual ** population,
		int populationSize,
		Individual * target
	);

	public:
};
