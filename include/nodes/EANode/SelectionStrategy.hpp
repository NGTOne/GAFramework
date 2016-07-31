#include "../../core/Genome.hpp"
#include "../../core/EABehaviourObject.hpp"
#include <random>
#include <string>
#include <vector>
#pragma once

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

	virtual unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<float> fitnesses
	)=0;

	virtual std::string toString();
};
