#include "instruments/population/TargetReachedGeneration.hpp"
#include <sstream>
#include <limits>
#include <math.h>

TargetReachedGeneration::TargetReachedGeneration(
	PopulationNode* target,
	std::string outFile,
	double targetFitness,
	double epsilon
) : CSVInstrument(target, outFile) {
	this->bestGeneration = 0;
	this->numAppearances = 0;
	this->bestFitness = std::numeric_limits<double>::lowest();
	this->targetFitness = targetFitness;
	this->epsilon = std::abs(epsilon);
	this->targetReachedGeneration = 0;
	this->targetReached = false;
	this->setHeader<std::string>({
		"Target Reached",
		"Optimum Generation",
		"Best Fitness Achieved",
		"Generation of Best Fitness",
		"Number of Appearances of Best Fitness"
	});
}

void TargetReachedGeneration::initialReport() {
	GenerationInfo info = this->evaluateNode();
	this->numAppearances = info.getAppearances();
	this->bestFitness = info.getBest();
	this->checkTargetReached(info);
}

void TargetReachedGeneration::runtimeReport() {
	GenerationInfo info = this->evaluateNode();

	if (info.getBest() > this->bestFitness) {
		this->bestFitness = info.getBest();
		this->numAppearances = info.getAppearances();
		this->bestGeneration = this->target->currentGeneration();
	}
	this->checkTargetReached(info);
}

void TargetReachedGeneration::endReport() {
	GenerationInfo info = this->evaluateNode();

	if (info.getBest() > this->bestFitness) {
		this->bestFitness = info.getBest();
		this->numAppearances = info.getAppearances();
		this->bestGeneration = this->target->currentGeneration();
	}
	this->checkTargetReached(info);

	std::map<std::string, std::string> results;
	results["Optimum Generation"] = this->stringify(
		this->targetReached ? this->targetReachedGeneration : 0
	);
	results["Target Reached"] = this->stringify(this->targetReached);
	results["Best Fitness Achieved"] = this->stringify(this->bestFitness);
	results["Generation of Best Fitness"] =
		this->stringify(this->bestGeneration);
	results["Number of Appearances of Best Fitness"] =
		this->stringify(this->numAppearances);

	this->write(results, std::string(""));
}

TargetReachedGeneration::GenerationInfo
	TargetReachedGeneration::evaluateNode()
{
	double bestFitness = std::numeric_limits<double>::lowest();
	unsigned int numAppearances = 0;
	std::vector<float> fitnesses = this->target->getFitnesses();

	for (float fitness: fitnesses) {
		if (fitness > bestFitness) {
			bestFitness = fitness;
			numAppearances = 1;
		} else if (fitness == bestFitness) {
			numAppearances += 1;
		}
	}

	return GenerationInfo(numAppearances, bestFitness);
}

void TargetReachedGeneration::checkTargetReached(GenerationInfo info) {
	if (this->targetReached) return;

	if (
		info.getBest() >= this->targetFitness - this->epsilon
		&& info.getBest() <= this->targetFitness + this->epsilon
	) {
		this->targetReachedGeneration =
			this->target->currentGeneration();
		this->targetReached = true;
	}
}

TargetReachedGeneration::GenerationInfo::GenerationInfo(
	unsigned int numAppearances,
	double bestFitness
) {
	this->numAppearances = numAppearances;
	this->bestFitness = bestFitness;
}

unsigned int TargetReachedGeneration::GenerationInfo::getAppearances() {
	return this->numAppearances;
}

double TargetReachedGeneration::GenerationInfo::getBest() {
	return this->bestFitness;
}
