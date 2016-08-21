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
	std::vector<Genome*> doReplacement(
		std::vector<Genome*> parents,
		std::vector<Genome*> offspring,
		std::vector<float>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives
	);

	public:
	using MuLambdaES::MuLambdaES;
};

#endif
