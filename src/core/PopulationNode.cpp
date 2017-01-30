#include "core/PopulationNode.hpp"
#include "core/utils/HierGC.hpp"
#include <sstream>

PopulationNode::PopulationNode(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName
) {
	this->init(
		populationSize,
		loci,
		objectives,
		populationToString,
		conditions,
		nodeName,
		1
	);
}

PopulationNode::PopulationNode(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName,
	unsigned int accelerationFactor
) {
	this->init(
		populationSize,
		loci,
		objectives,
		populationToString,
		conditions,
		nodeName,
		accelerationFactor
	);
}

PopulationNode::~PopulationNode() {
	for (unsigned int i = 0; i < this->population.size(); i++)
		delete(this->population[i]);
}

void PopulationNode::registerInternalObjects() {
	HierGC::registerObjects(this->objectives);
	HierGC::registerObjects(this->conditions);
	HierGC::registerObjects(this->canonicalLoci);
	HierGC::registerObject(this->populationToString);
}

void PopulationNode::init(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName,
	unsigned int accelerationFactor
) {
	this->initialPopulationSize = populationSize;
	this->objectives = objectives;
	this->populationToString = populationToString;
	this->conditions = conditions;
	this->nodeName = nodeName;
	this->accelerationFactor = accelerationFactor;
	this->currentIteration = 0;
	this->readOnce = false;

	this->createLoci(loci);
}

float PopulationNode::evaluateFitness(Genome* target) {
	float total = 0;
	for (unsigned int i = 0; i < this->objectives.size(); i++)
		total += this->objectives[i]->checkFitness(target);

	return total;
}

float PopulationNode::evaluateFitness(unsigned int solutionIndex) {
	Genome* genome = this->getIndex(solutionIndex);
	return this->evaluateFitness(genome);
}

void PopulationNode::createLoci(std::vector<Locus*> loci) {
	for (unsigned int i = 0; i < this->population.size(); i++) 
		delete(this->population[i]);
	this->population.clear();
	this->fitnesses = std::vector<float>(this->initialPopulationSize, 0);

	for (unsigned int i = 0; i < this->initialPopulationSize; i++)
		this->population.push_back(new Genome(loci, this->nodeName));
	this->evaluateFitnesses();
	this->canonicalLoci = loci;
	HierGC::registerObjects(loci);
}

void PopulationNode::addObjective(ObjectiveFunction* objective) {
	this->objectives.push_back(objective);
	HierGC::registerObject(objective);
	this->evaluateFitnesses();
}

void PopulationNode::addObjectives(std::vector<ObjectiveFunction*> objectives) {
	for (unsigned int i = 0; i < objectives.size(); i++)
		this->objectives.push_back(objectives[i]);
	HierGC::registerObjects(objectives);
	this->evaluateFitnesses();
}

void PopulationNode::setObjective(ObjectiveFunction* objective) {
	this->objectives.clear();
	this->addObjective(objective);
}

void PopulationNode::setObjectives(std::vector<ObjectiveFunction*> objectives) {
	this->objectives.clear();
	this->addObjectives(objectives);
}

void PopulationNode::addEndCondition(EndCondition* condition) {
	this->conditions.push_back(condition);
	HierGC::registerObject(condition);
}

void PopulationNode::addEndConditions(std::vector<EndCondition*> conditions) {
	for (unsigned int i = 0; i < conditions.size(); i++)
		this->conditions.push_back(conditions[i]);
	HierGC::registerObjects(conditions);
}

void PopulationNode::setEndCondition(EndCondition* condition) {
	this->conditions.clear();
	this->addEndCondition(condition);
}

void PopulationNode::setEndConditions(std::vector<EndCondition*> conditions) {
	this->conditions.clear();
	this->addEndConditions(conditions);
}

void PopulationNode::addLoci(std::vector<Locus*> loci) {
	std::vector<Locus*> templateLoci = this->canonicalLoci;
	templateLoci.insert(templateLoci.end(), loci.begin(), loci.end());
	this->createLoci(templateLoci);
}

void PopulationNode::setLoci(std::vector<Locus*> loci) {
	this->createLoci(loci);
}

void PopulationNode::setToString(ToStringFunction* populationToString) {
	this->populationToString = populationToString;
	HierGC::registerObject(this->populationToString);
}

void PopulationNode::replacePopulation() {
	std::vector<Genome*> tempPopulation = this->getNextPopulation();
	for (unsigned int i = 0; i < this->population.size(); i++)
		delete(this->population[i]);
	this->population = tempPopulation;
}

void PopulationNode::nextIteration() {
	unsigned int i = 0;
	while (!done() && i++ < this->accelerationFactor) {
		if (this->isHierarchical()) this->evaluateFitnesses();
		this->replacePopulation();
		this->currentIteration++;
	}
}

Genome* PopulationNode::getIndex(unsigned int index) {
	return this->population[index];
}

bool PopulationNode::done() {
	// TODO: Allow logical operations (AND/OR) of end conditions
	for (unsigned int i = 0; i < this->conditions.size(); i++)
		if (this->conditions[i]->checkCondition(
			this->population,
			this->fitnesses,
			this->currentIteration
		)) return true;

	return false;
}

// Since our n is reasonably small, the O(n^2) bubblesort will suffice
void PopulationNode::sortPopulation() {
	for (unsigned int i = 0; i < this->population.size(); i++) {
		for (unsigned int k = 0; k < this->population.size(); k++) {
			if (this->fitnesses[i] > this->fitnesses[k]) {
				float tempFitness = fitnesses[i];
				Genome* tempSolution = population[i];

				this->fitnesses[i] = this->fitnesses[k];
				this->population[i] = this->population[k];

				this->fitnesses[k] = tempFitness;
				this->population[k] = tempSolution;
			}
		}
	}
}

void PopulationNode::evaluateFitnesses() {
	for (unsigned int i = 0; i < this->population.size(); i++)
		this->fitnesses[i] = this->evaluateFitness(i);
}

void PopulationNode::insert(unsigned int index, Genome* target) {
	delete(this->population[index]);
	this->evaluateFitness(index);
}

std::string PopulationNode::name() {
	return this->nodeName;
}

unsigned int PopulationNode::populationSize() {
	return this->population.empty() ?
		this->initialPopulationSize : this->population.size();
}

unsigned int PopulationNode::currentGeneration() {
	return this->currentIteration;
}

std::string PopulationNode::populationStrings() {
	std::stringstream ss;
	std::string populationString;
	
	for (unsigned int i = 0; i < population.size(); i++) {
		populationString = this->populationToString->toString(
			this->population[i]
		);

		ss << "Member " << i << ": " << populationString
			<< " Fitness: " << this->fitnesses[i] << "\n";
	}

	return ss.str();
}

std::string PopulationNode::toString() {
	std::stringstream ss;

	ss << "Population size: " << this->population.size() << "\n";
	ss << this->populationStrings();

	this->readOnce = true;
	return ss.str();
}

std::set<Locus*> PopulationNode::getLoci() {
	return std::set<Locus*>(
		this->canonicalLoci.begin(),
		this->canonicalLoci.end()
	);
}

std::set<Locus*> PopulationNode::getConstructiveLoci() {
	std::set<Locus*> loci;
	for (unsigned int i = 0; i < this->canonicalLoci.size(); i++)
		if (this->canonicalLoci[i]->isConstructive()) loci.insert(
			this->canonicalLoci[i]
		);

	return loci;
}

std::vector<Locus*> PopulationNode::getCanonicalLoci() {
	return this->canonicalLoci;
}

std::vector<EndCondition*> PopulationNode::getConditions() {
	return this->conditions;
}

std::vector<ObjectiveFunction*> PopulationNode::getObjectives() {
	return this->objectives;
}

ToStringFunction * PopulationNode::getToString() {
	return this->populationToString;
}

float PopulationNode::getFitnessAtIndex(unsigned int index) {
	return this->fitnesses[index];
}

std::vector<float> PopulationNode::getFitnesses() {
	return this->fitnesses;
}

bool PopulationNode::contains(Genome* target) {
	for (unsigned int i = 0; i < this->population.size(); i++)
		if (this->population[i] == target) return true;
	return false;
}

bool PopulationNode::usesSpecies(Genome* target) {
	return this->nodeName == target->getSpeciesNode();
}

bool PopulationNode::isHierarchical() {
	return this->getConstructiveLoci().empty();
}
