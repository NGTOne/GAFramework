#ifndef NODES_EANODE_SYSTEMS_ES_MuPlusLambdaES
#define NODES_EANODE_SYSTEMS_ES_MuPlusLambdaES

#include "nodes/EANode/MutationOperation.hpp"
#include "nodes/EANode/CrossoverOperation.hpp"
#include "nodes/EANode/SelectionStrategy.hpp"
#include "MuLambdaES.hpp"
#include <vector>

class MuPlusLambdaES: public MuLambdaES {
	private:

	protected:
	std::vector<Genome*> doReplacement(
		std::vector<Genome*> parents,
		std::vector<Genome*> offspring,
		std::vector<Fitness>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives
	);

	public:
	using MuLambdaES::MuLambdaES;
};

#endif
