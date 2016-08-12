#ifndef CORE_PopulationNode
#define CORE_PopulationNode
#include "Genome.hpp"
#include "ObjectiveFunction.hpp"
#include "EndCondition.hpp"
#include "ObjectiveFunction.hpp"
#include "ToStringFunction.hpp"
#include "Locus.hpp"
#include "EABehaviourObject.hpp"
#include <vector>
#include <set>

typedef std::string node_type_t;

class PopulationNode : public EABehaviourObject {
	private:

	protected:
	std::vector<Genome*> population;
	std::vector<float> fitnesses;
	std::string nodeName;

	unsigned int currentIteration;
	unsigned int accelerationFactor;
	unsigned int initialPopulationSize;
	std::vector<Locus*> canonicalLoci;
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

	float evaluateFitness(unsigned int solutionIndex);
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
	virtual void registerInternalObjects();

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
	Genome * getIndex(unsigned int index);
	virtual std::vector<Genome*> getNextPopulation()=0;
	virtual bool done();

	virtual void sortPopulation();
	void evaluateFitnesses();
	float evaluateFitness(Genome * target);

	// For migration
	virtual void insert(unsigned int index, Genome * target);

	std::string name();
	unsigned int populationSize();
	unsigned int currentGeneration();
	bool contains(Genome * target);
	bool usesSpecies(Genome * target);

	std::string populationStrings();
	virtual std::string toString();
	virtual node_type_t type()=0;

	std::set<Locus*> getLoci();
	std::set<Locus*> getConstructiveLoci();
	std::vector<Locus*> getCanonicalLoci();
	std::vector<EndCondition*> getConditions();
	std::vector<ObjectiveFunction*> getObjectives();
	ToStringFunction * getToString();
	float getFitnessAtIndex(unsigned int index);
	std::vector<float> getFitnesses();

	virtual PopulationNode * duplicate(std::string newNodeName)=0;
};

#endif
#pragma once
