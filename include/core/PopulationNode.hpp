#include "Genome.hpp"
#include "ObjectiveFunction.hpp"
#include "EndCondition.hpp"
#include "ObjectiveFunction.hpp"
#include "ToStringFunction.hpp"
#include "Locus.hpp"
#include <vector>
#include <set>
#pragma once

typedef std::string node_type_t;

class PopulationNode {
	private:

	protected:
	std::vector<Genome*> population;
	std::vector<int> fitnesses;
	std::string nodeName;

	int currentIteration;
	unsigned int accelerationFactor;
	unsigned int initialPopulationSize;
	std::vector<EndCondition *> conditions;

	std::vector<ObjectiveFunction*> objectives;
	ToStringFunction * populationToString;

	//Used to decrease unnecessary verbosity in toString()
	bool readOnce;

	void init(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string nodeName,
		unsigned int accelerationFactor
	);

	int evaluateFitness(int solutionIndex);
	void createLoci(std::vector<Locus*> loci);
	void replacePopulation();

	public:
	PopulationNode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string nodeName
	);

	PopulationNode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string nodeName,
		unsigned int accelerationFactor
	);

	virtual ~PopulationNode();

	void addObjective(ObjectiveFunction * objective);
	void addObjectives(std::vector<ObjectiveFunction*> objectives);
	void setObjective(ObjectiveFunction * objective);
	void setObjectives(std::vector<ObjectiveFunction*> objectives);

	void addEndCondition(EndCondition * condition);
	void addEndConditions(std::vector<EndCondition *> conditions);
	void setEndCondition(EndCondition * condition);
	void setEndConditions(std::vector<EndCondition *> conditions);

	void addLoci(std::vector<Locus*> loci);
	void setLoci(std::vector<Locus*> loci);
	void setToString(ToStringFunction * populationToString);

	// Iteration mechanics
	virtual void nextIteration();
	Genome * getIndex(int index);
	virtual std::vector<Genome*> getNextPopulation()=0;
	virtual bool done();

	virtual void sortPopulation();
	void evaluateFitnesses();
	int evaluateFitness(Genome * target);

	// For migration
	virtual void insert(int index, Genome * target);

	std::string name();
	unsigned int populationSize();
	bool contains(Genome * target);

	std::string populationStrings();
	virtual std::string toString();
	std::string stringifyGenome(Genome * target);
	virtual node_type_t type()=0;

	std::set<Locus*> getLoci();
	std::set<Locus*> getConstructiveLoci();
	std::vector<EndCondition*> getConditions();
	std::vector<ObjectiveFunction*> getObjectives();
	ToStringFunction * getToString();
	int getFitnessAtIndex(int index);
};
