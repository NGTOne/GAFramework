#include "Genome.hpp"
#include "ObjectiveFunction.hpp"
#include "EndCondition.hpp"
#include "ObjectiveFunction.hpp"
#include "ToStringFunction.hpp"
#include "Locus.hpp"
#include <vector>
#pragma once

typedef std::string node_type_t;

class PopulationNode {
	private:

	protected:
	std::vector<Genome*> population;
	std::vector<int> fitnesses;
	std::string nodeName;

	int currentIteration;
	int accelerationFactor;
	int initialPopulationSize; // For generating the initial population
	std::vector<EndCondition *> conditions;

	std::vector<ObjectiveFunction*> objectives;
	ToStringFunction * populationToString;

	//Used to decrease unnecessary verbosity in toString()
	bool readOnce;

	void init(
		int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string nodeName,
		int accelerationFactor
	);

	int evaluateFitness(Genome * target);
	int evaluateFitness(int solutionIndex);
	void createLoci(std::vector<Locus*> loci);
	void replacePopulation();

	public:
	PopulationNode(
		int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string nodeName
	);

	PopulationNode(
		int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string nodeName,
		int accelerationFactor
	);

	~PopulationNode();

	void addEndCondition(EndCondition * condition);
	void addEndConditions(std::vector<EndCondition *> conditions);
	void setEndCondition(EndCondition * condition);
	void setEndConditions(std::vector<EndCondition *> conditions);

	void addLoci(std::vector<Locus*> loci);

	// Iteration mechanics
	virtual void nextIteration();
	Genome * getIndex(int index);
	virtual std::vector<Genome*> getNextPopulation()=0;
	virtual bool done();

	virtual void sortPopulation();
	void evaluateFitnesses();

	// For migration
	virtual void insert(int index, Genome * target);

	std::string name();
	int populationSize();

	std::string populationStrings();
	virtual std::string toString();
	virtual node_type_t type()=0;
};
