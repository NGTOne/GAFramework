#ifndef NODES_EANODE_SYSTEMS_ES_CMSA_ES
#define NODES_EANODE_SYSTEMS_ES_CMSA_ES

#include "MuCommaLambdaES.hpp"
#include "../../mutations/AdaptiveRealValueMutation.hpp"
#include <Eigen/Dense>

class CMSA_ES: public MuCommaLambdaES {
	private:
	class CMSAMutation : public AdaptiveRealValueMutation {
		private:

		protected:
		double tauC;
		unsigned int mu;
		unsigned int lambda;
		Eigen::MatrixXd C;

		double sigmaAvg;
		std::vector<double> xAvg;

		void calculateTaus(Genome* initial);
		void calculateProperGenomeLengths(Genome* initial);
		void otherSetupSteps(Genome* initial);

		void setMu(unsigned int mu);
		void calculateAverages(std::vector<Genome*> population);

		Genome* addStdDevs(Genome* target);
		Genome* mutateProper(Genome* target);

		public:
		CMSAMutation(unsigned int lambda);
		CMSAMutation(unsigned int lambda, double tau, double tauC);
	};

	protected:

	public:
	CMSA_ES(unsigned int lambda);
	CMSA_ES(unsigned int lambda, double tau, double tauC);
};

#endif
