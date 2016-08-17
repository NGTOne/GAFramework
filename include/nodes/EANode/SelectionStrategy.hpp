#ifndef NODES_EANODE_SelectionStrategy
#define NODES_EANODE_SelectionStrategy

#include "../../core/Genome.hpp"
#include "../../core/EABehaviourObject.hpp"
#include <string>
#include <vector>

class SelectionStrategy : public EABehaviourObject {
	private:

	protected:
	std::string name;

	double crossoverRate;

	SelectionStrategy(double crossoverRate, std::string name);

	void init(
		double crossoverRate,
		std::string name
	);

	public:
	SelectionStrategy(double crossoverRate);
	virtual ~SelectionStrategy();

	std::vector<Genome*> chooseParents(
		std::vector<Genome*> population,
		std::vector<float> fitnesses,
		unsigned int count
	);

	virtual unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<float> fitnesses
	)=0;

	virtual std::string toString();
};

#endif
