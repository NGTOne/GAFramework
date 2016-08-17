#ifndef NODES_EANODE_SYSTEMS_ES_MuCommaLambdaES
#define NODES_EANODE_SYSTEMS_ES_MuCommaLambdaES

#include "../../MutationOperation.hpp"
#include "../../CrossoverOperation.hpp"
#include "../../SelectionStrategy.hpp"
#include "MuLambdaES.hpp"
#include <vector>

class MuCommaLambdaES: public MuLambdaES {
	private:

	protected:
	MuCommaLambdaES(MutationOperation* mutation, unsigned int lambda = 1);
	MuCommaLambdaES(
		MutationOperation* mutation,
		SelectionStrategy* selection,
		unsigned int lambda = 1
	);
	MuCommaLambdaES(
		CrossoverOperation* cross,
		MutationOperation* mutation,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
	MuCommaLambdaES(
		SelectionStrategy* strategy,
		CrossoverOperation* cross,
		MutationOperation* mutation,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);

	std::vector<Genome*> doReplacement(
		std::vector<Genome*> parents,
		std::vector<Genome*> offspring,
		std::vector<float>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives
	);

	public:
};

#endif
