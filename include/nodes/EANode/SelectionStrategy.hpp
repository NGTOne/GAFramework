#include "../../core/Genome.hpp"
#include <random>
#include <string>
#include <vector>
#pragma once

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	std::mt19937 generator;
	std::string name;

	double crossoverRate;

	SelectionStrategy(
		unsigned seed,
		double crossoverRate,
		std::string name
	);

	void init(
		double crossoverRate,
		unsigned seed,
		std::string name
	);

	public:

	SelectionStrategy(double crossoverRate);
	SelectionStrategy(double crossoverRate, unsigned seed);

	virtual int getParent(
		std::vector<Genome*> population,
		std::vector<int> fitnesses
	)=0;

	virtual std::string toString();
};
