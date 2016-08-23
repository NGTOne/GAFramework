#ifndef NODES_EANODE_MUTATIONS_CovarianceMatrixSelfAdaptiveMutation
#define NODES_EANODE_MUTATIONS_CovarianceMatrixSelfAdaptiveMutation

#include "AdaptiveRealValueMutation.hpp"
#include <Eigen/Dense>

class CovarianceMatrixSelfAdaptiveMutation: public AdaptiveRealValueMutation {
	private:

	protected:
	double tauC;
	unsigned int mu;
	unsigned int lambda;
	Eigen::MatrixXd C;

	void calculateTaus(Genome* initial);
	void calculateProperGenomeLengths(Genome* initial);
	void otherSetupSteps(Genome* initial);

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
