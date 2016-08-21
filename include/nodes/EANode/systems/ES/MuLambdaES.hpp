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

		protected:
		Gene* newLocusValue(Gene* current);
		Gene* newLocusValue(
			Genome* current,
			unsigned int index,
			MutationOperation* mutation
		);

		void calculateTaus(Genome* initial);
		Genome* addStdDevs(Genome* target);
		std::vector<Gene*> adjustStdDevs(std::vector<Gene*> genes);
		std::vector<MutationOperation*> getMutations(Genome* target);
		void cleanUpMutations(std::vector<MutationOperation*> mutations);

		public:
		AdjustableESMutation();
		AdjustableESMutation(double tau, double tauPrime);
		Genome* mutate(Genome* initialGenome);
	};

	protected:
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

	public:
};

#endif
