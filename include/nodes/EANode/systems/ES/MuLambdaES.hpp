#ifndef NODES_EANODE_SYSTEMS_ES_MuLambdaES
#define NODES_EANODE_SYSTEMS_ES_MuLambdaES

#include "../../MutationOperation.hpp"
#include "../../CrossoverOperation.hpp"
#include "../../SelectionStrategy.hpp"
#include "../ES.hpp"
#include <vector>
#include <map>

class MuLambdaES: public ES {
	private:
	unsigned int lambda;
	unsigned int rho;

	void init(unsigned int lambda);
	void init(unsigned int lambda, unsigned int rho);

	class AdjustableESMutation: public MutationOperation {
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
		AdjustableESMutation();
		AdjustableESMutation(double tau, double tauPrime);
		Genome* mutate(Genome* initialGenome);
	};

	protected:

	public:
	MuLambdaES(unsigned int lambda = 1);
	MuLambdaES(double tau, double tauPrime, unsigned int lambda = 1);

	MuLambdaES(SelectionStrategy* selection, unsigned int lambda = 1);
	MuLambdaES(
		SelectionStrategy* selection,
		double tau,
		double tauPrime,
		unsigned int lambda = 1
	);

	MuLambdaES(
		CrossoverOperation* cross,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
	MuLambdaES(
		CrossoverOperation* cross,
		double tau,
		double tauPrime,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);

	MuLambdaES(
		SelectionStrategy* selection,
		CrossoverOperation* cross,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
	MuLambdaES(
		SelectionStrategy* selection,
		CrossoverOperation* cross,
		double tau,
		double tauPrime,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);

	MuLambdaES(MutationOperation* mutation, unsigned int lambda = 1);
	MuLambdaES(
		MutationOperation* mutation,
		SelectionStrategy* selection,
		unsigned int lambda = 1
	);
	MuLambdaES(
		CrossoverOperation* cross,
		MutationOperation* mutation,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
	MuLambdaES(
		SelectionStrategy* strategy,
		CrossoverOperation* cross,
		MutationOperation* mutation,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);

	std::vector<Genome*> getOffspring(
		std::vector<Genome*> parents,
		std::vector<float> parentFitnesses,
		std::string speciesNode
	);
};

#endif
