#ifndef NODES_EANODE_SYSTEMS_ES_MuLambdaES
#define NODES_EANODE_SYSTEMS_ES_MuLambdaES

#include "../../MutationOperation.hpp"
#include "../../CrossoverOperation.hpp"
#include "../../SelectionStrategy.hpp"
#include "../../systems/ES.hpp"
#include <vector>
#include <map>

class MuLambdaES: public ES {
	private:
	unsigned int lambda;
	unsigned int rho;

	void init(unsigned int lambda);
	void init(unsigned int lambda, unsigned int rho);

	protected:

	public:
	MuLambdaES(unsigned int lambda = 1);
	MuLambdaES(SelectionStrategy* selection, unsigned int lambda = 1);
	MuLambdaES(
		CrossoverOperation* cross,
		unsigned int lambda = 1,
		unsigned int rho = 2
	);
	MuLambdaES(
		SelectionStrategy* selection,
		CrossoverOperation* cross,
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

	virtual std::vector<Genome*> getOffspring(
		std::vector<Genome*> parents,
		std::vector<Fitness> parentFitnesses,
		std::string speciesNode
	);
};

#endif
