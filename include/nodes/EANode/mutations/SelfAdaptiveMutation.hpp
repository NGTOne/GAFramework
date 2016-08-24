#ifndef NODES_EANODE_MUTATIONS_SelfAdaptiveMutation
#define NODES_EANODE_MUTATIONS_SelfAdaptiveMutation

#include "AdaptiveRealValueMutation.hpp"

class SelfAdaptiveMutation: public AdaptiveRealValueMutation {
	private:

	protected:
	double tauPrime;
	bool useTauPlusOneCorrection;

	void calculateTaus(Genome* initial);
	void calculateProperGenomeLengths(Genome* initial);

	Genome* addStdDevs(Genome* target);
	Genome* mutateProper(Genome* target);

	public:
	SelfAdaptiveMutation(bool useTauPlusOneCorrection = true);
	SelfAdaptiveMutation(
		double tau,
		double tauPrime,
		bool useTauPlusOneCorrection = true
	);
};

#endif
