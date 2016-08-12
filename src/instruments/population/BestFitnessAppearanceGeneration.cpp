#include "instruments/population/BestFitnessAppearanceGeneration.hpp"
#include <sstream>
#include <limits>

BestFitnessAppearanceGeneration::BestFitnessAppearanceGeneration(
	PopulationNode* target,
	std::string outFile
) : PopulationInstrument(target, outFile) {
	this->bestGeneration = 0;
	this->numAppearances = 0;
	this->bestFitness = std::numeric_limits<double>::lowest();
}

void BestFitnessAppearanceGeneration::initialReport() {
	GenerationInfo info = this->evaluateNode();
	this->numAppearances = info.getAppearances();
	this->bestFitness = info.getBest();
}

void BestFitnessAppearanceGeneration::runtimeReport() {
	GenerationInfo info = this->evaluateNode();

	if (info.getBest() > this->bestFitness) {
		this->bestFitness = info.getBest();
		this->numAppearances = info.getAppearances();
		this->bestGeneration = this->target->currentGeneration();
	}
}

void BestFitnessAppearanceGeneration::endReport() {
	GenerationInfo info = this->evaluateNode();

	if (info.getBest() > this->bestFitness) {
		this->bestFitness = info.getBest();
		this->numAppearances = info.getAppearances();
		this->bestGeneration = this->target->currentGeneration();
	}

	std::stringstream ss;
	ss << "Node " << this->target->name()
		<< " achieved a best fitness of " << this->bestFitness
		<< " for " << this->numAppearances << " individuals"
		<< " at generation " << this->bestGeneration << ".\n";
	this->write(ss.str());
}

BestFitnessAppearanceGeneration::GenerationInfo
	BestFitnessAppearanceGeneration::evaluateNode()
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

BestFitnessAppearanceGeneration::GenerationInfo::GenerationInfo(
	unsigned int numAppearances,
	double bestFitness
) {
	this->numAppearances = numAppearances;
	this->bestFitness = bestFitness;
}

unsigned int BestFitnessAppearanceGeneration::GenerationInfo::getAppearances() {
	return this->numAppearances;
}

double BestFitnessAppearanceGeneration::GenerationInfo::getBest() {
	return this->bestFitness;
}
