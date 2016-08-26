#ifndef NODES_EANODE_MUTATIONS_VEDAMutation
#define NODES_EANODE_MUTATIONS_VEDAMutation

#include "AdaptiveRealValueMutation.hpp"
#include <Eigen/Core>

class VEDAMutation : public AdaptiveRealValueMutation {
	private:

	protected:
	double tauC;
	unsigned int mu;
	unsigned int lambda;
	Eigen::MatrixXd C;
	Eigen::MatrixXd sqrtC;

	double sigmaAvg;
	std::vector<double> xAvg;
	std::vector<Eigen::VectorXd> skCollection;

	void calculateTaus(Genome* initial);
	void calculateProperGenomeLengths(Genome* initial);
	void otherSetupSteps(Genome* initial);

	Genome* addStdDevs(Genome* target);
	Genome* mutateProper(Genome* target);

	public:
	VEDAMutation();
	VEDAMutation(unsigned int lambda);
	VEDAMutation(unsigned int lambda, double tau, double tauC);

	void setLambda(unsigned int lambda);
	void setMu(unsigned int mu);
	void calculateAverages(std::vector<Genome*> population);
};

#endif
