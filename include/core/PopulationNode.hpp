#include "Genome.hpp"
#include "ObjectiveFunction.hpp"
#include <vector>

class PopulationNode {
	private:

	protected:
	std::vector<Genome*> population;
	std::vector<std::vector<int>> assignedFitnesses;
	std::vector<int> fitnesses;
	std::string name;

	int maxIterations;
	int currentIteration;
	int accelerationFactor;
	std::vector<EndCondition *> conditions;
	bool done;

	std::vector<ObjectiveFunction*> objectives;
	ToStringFunction * populationToString;

	//Used to decrease unnecessary verbosity in toString()
	bool readOnce;

	void init(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		int accelerationFactor
	);

	public:
	PopulationNode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name
	);

	PopulationNode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		int accelerationFactor
	);

	~PopulationNode();

	void addEndCondition(EndCondition * condition);
	void addEndConditions(std::vector<EndCondition *> conditions);
	void setEndCondition(EndCondition * condition);
	void setEndConditions(std::vector<EndCondition *> conditions);

	void addLoci(std::string format, ...);

	// Iteration mechanics
	virtual void nextIteration()=0;
	Genome * getIndex(int index);
	virtual std::vector<Genome*> getNextPopulation()=0;
	virtual bool done();

	virtual void sortPopulation();
	void evaluateFitnesses();

	// For migration
	virtual void insert(int index, Genome * target);

	std::string populationStrings();
	virtual std::string toString();
};
