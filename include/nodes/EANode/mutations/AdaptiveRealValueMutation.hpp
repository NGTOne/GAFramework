#ifndef NODES_EANODE_MUTATIONS_AdaptiveRealValueMutation
#define NODES_EANODE_MUTATIONS_AdaptiveRealValueMutation

#include "../MutationOperation.hpp"
#include <vector>
#include "../../../core/Locus.hpp"
#include "../../../core/genes/Gene.hpp"

class AdaptiveRealValueMutation: public MutationOperation {
	private:
	std::vector<unsigned int> stdDevIndices;
	unsigned int initialGenomeLength;
	unsigned int targetGenomeLength;
	double tau;
	double tauPrime;
	bool tausCalculated;
	Locus* stdDevLocus;

	bool setupDone;

	void setupInternals(Genome* firstTarget);

	protected:
	Gene* newLocusValue(Gene* current);

	void calculateTaus(Genome* initial);
	Genome* addStdDevs(Genome* target);
	Genome* mutateProper(Genome* target);

	public:
	AdaptiveRealValueMutation();
	AdaptiveRealValueMutation(double tau, double tauPrime);
	Genome* mutate(Genome* initialGenome);
};

#endif
