#ifndef NODES_EANODE_MUTATIONS_CovarianceMatrixSelfAdaptiveMutation
#define NODES_EANODE_MUTATIONS_CovarianceMatrixSelfAdaptiveMutation

#include "AdaptiveRealValueMutation.hpp"

class CovarianceMatrixSelfAdaptiveMutation: public AdaptiveRealValueMutation {
	private:

	protected:
	double tauC;
	unsigned int mu;
	unsigned int lambda;

	void calculateTaus(Genome* initial);
	void calculateProperGenomeLengths(Genome* initial);

	Genome* addStdDevs(Genome* target);
	Genome* mutateProper(Genome* target);

	public:
	CovarianceMatrixSelfAdaptiveMutation(
		unsigned int mu,
		unsigned int lambda
	);
	CovarianceMatrixSelfAdaptiveMutation(
		unsigned int mu,
		unsigned int lambda,
		double tau,
		double tauC
	);
};

#endif
