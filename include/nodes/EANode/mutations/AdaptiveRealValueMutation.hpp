#ifndef NODES_EANODE_MUTATIONS_AdaptiveRealValueMutation
#define NODES_EANODE_MUTATIONS_AdaptiveRealValueMutation

#include "../MutationOperation.hpp"
#include <vector>
#include "../../../core/Locus.hpp"
#include "../../../core/genes/Gene.hpp"

class AdaptiveRealValueMutation: public MutationOperation {
	private:

	protected:
	std::vector<unsigned int> stdDevIndices;
	unsigned int initialGenomeLength;
	unsigned int targetGenomeLength;
	double tau;
	bool tausCalculated;
	Locus* stdDevLocus;

	bool setupDone;

	Gene* newLocusValue(Gene* current); // stub

	virtual void setupInternals(Genome* firstTarget);
	virtual void calculateTaus(Genome* initial)=0;
	virtual void calculateProperGenomeLengths(Genome* initial)=0;

	virtual Genome* addStdDevs(Genome* target)=0;
	virtual Genome* mutateProper(Genome* target)=0;

	public:
	AdaptiveRealValueMutation();
	Genome* mutate(Genome* initialGenome);
};

#endif
