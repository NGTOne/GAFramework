#ifndef NODES_EANODE_MUTATIONS_SelfAdaptiveMutation
#define NODES_EANODE_MUTATIONS_SelfAdaptiveMutation

#include "AdaptiveRealValueMutation.hpp"

class SelfAdaptiveMutation: public AdaptiveRealValueMutation {
	private:

	protected:
	double tauPrime;

	void calculateTaus(Genome* initial);
	void calculateProperGenomeLengths(Genome* initial);

	Genome* addStdDevs(Genome* target);
	Genome* mutateProper(Genome* target);

	public:
	SelfAdaptiveMutation();
	SelfAdaptiveMutation(double tau, double tauPrime);
};

#endif
