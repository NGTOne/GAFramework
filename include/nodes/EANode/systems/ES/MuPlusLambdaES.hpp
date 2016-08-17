#ifndef NODES_EANODE_SYSTEMS_ES_MuPlusLambdaES
#define NODES_EANODE_SYSTEMS_ES_MuPlusLambdaES

#include "../../MutationOperation.hpp"
#include "../../CrossoverOperation.hpp"
#include "../../SelectionStrategy.hpp"
#include "MuLambdaES.hpp"
#include <vector>

class MuPlusLambdaES: public MuLambdaES {
	private:

	protected:
	std::vector<Genome*> doReplacement(
		std::vector<Genome*> parents,
		std::vector<Genome*> offspring,
		std::vector<float>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives
	);

	public:
	MuPlusLambdaES(MutationOperation* mutation, unsigned int lambda = 1);
	MuPlusLambdaES(
		MutationOperation* mutation,
		SelectionStrategy* selection,
		unsigned int lambda = 1
	);
	MuPlusLambdaES(
		CrossoverOperation* cross,
		MutationOperation* mutation,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
	MuPlusLambdaES(
		SelectionStrategy* strategy,
		CrossoverOperation* cross,
		MutationOperation* mutation,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
};

#endif
