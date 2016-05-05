#include "Solution.hpp"
#include "ObjectiveFunction.hpp"
#include <vector>

class PopulationNode {
	private:

	protected:
	std::vector<Solution*> population;
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
		std::string name,
		int maxIterations,
		int accelerationFactor
	);

	public:
	PopulationNode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::string name,
	);

	PopulationNode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
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
	Solution * getIndex(int index);
	virtual std::vector<Solution*> getNextPopulation()=0;
	virtual bool done();

	virtual void sortPopulation();
	void evaluateFitnesses();

	// For migration
	virtual void insert(int index, Solution * target);

	std::string populationStrings();
	virtual std::string toString();
};
