#ifndef NODES_EANODE_SYSTEMS_ES_VEDA_ES
#define NODES_EANODE_SYSTEMS_ES_VEDA_ES

#include "MuCommaLambdaES.hpp"
#include "../../mutations/AdaptiveRealValueMutation.hpp"
#include <Eigen/Core>

class VEDA_ES: public MuCommaLambdaES {
	private:
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
		VEDAMutation(unsigned int lambda);
		VEDAMutation(unsigned int lambda, double tau, double tauC);

		void setMu(unsigned int mu);
		void calculateAverages(std::vector<Genome*> population);
	};

	protected:

	public:
	VEDA_ES(unsigned int lambda, CrossoverOperation* cross = NULL);
	VEDA_ES(
		unsigned int lambda,
		double tau,
		double tauC,
		CrossoverOperation* cross = NULL
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
