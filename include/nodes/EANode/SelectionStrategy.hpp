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

	SelectionStrategy(double crossoverRate, std::string name);
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
	virtual ~SelectionStrategy();

	virtual unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<float> fitnesses
	)=0;

	virtual std::string toString();
};
