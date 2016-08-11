#include "core/migration/MigratoryRelationship.hpp"
#include "core/migration/NullTranslationFunction.hpp"
#include "core/PopulationNode.hpp"
#include "core/HierRNG.hpp"
#include <random>
#include <chrono>

MigratoryRelationship::MigratoryRelationship(
	PopulationNode* fromNode,
	PopulationNode* toNode,
	unsigned int n
) {
	this->init(
		fromNode,
		toNode,
		n,
		TranslationFunction(),
		TranslationFunction()
	);
}

MigratoryRelationship::MigratoryRelationship(
	PopulationNode* fromNode,
	PopulationNode* toNode,
	unsigned int n,
	TranslationFunction toTranslate
) {
	this->init(
		fromNode,
		toNode,
		n,
		toTranslate,
		NullTranslationFunction()
	);
}

MigratoryRelationship::MigratoryRelationship(
	PopulationNode* fromNode,
	PopulationNode* toNode,
	unsigned int n,
	TranslationFunction toTranslate,
	TranslationFunction fromTranslate
) {
	this->init(fromNode, toNode, n, toTranslate, fromTranslate);
}

void MigratoryRelationship::init(
	PopulationNode* fromNode,
	PopulationNode* toNode,
	unsigned int n,
	TranslationFunction toTranslate,
	TranslationFunction fromTranslate
) {
	this->fromNode = fromNode;
	this->toNode = toNode;
	this->n = n;
	this->toTranslate = toTranslate;
	this->fromTranslate = fromTranslate;
}

void MigratoryRelationship::swap(
	unsigned int fromNodeIndex,
	unsigned int toNodeIndex
) {
	Genome* fromNodeInsert,
		* toNodeInsert,
		* fromNodeOriginal,
		* toNodeOriginal;

	fromNodeOriginal = fromNode->getIndex(fromNodeIndex);
	toNodeOriginal = toNode->getIndex(toNodeIndex);

	toNodeInsert = this->toTranslate.createTranslatedGenome(
		fromNodeOriginal,
		this->toNode->name()
	);
	fromNodeInsert = this->fromTranslate.createTranslatedGenome(
		toNodeOriginal,
		this->fromNode->name()
	);

	toNode->insert(toNodeIndex, toNodeInsert);
	fromNode->insert(fromNodeIndex, fromNodeInsert);
}

void MigratoryRelationship::oneWayMigrate(
	unsigned int fromNodeIndex,
	unsigned int toNodeIndex
) {
	Genome* original, * insert;

	original = fromNode->getIndex(fromNodeIndex);
	insert = toTranslate.createTranslatedGenome(
		original,
		this->toNode->name()
	);
	toNode->insert(toNodeIndex, insert);
}

void MigratoryRelationship::migrate() {
	unsigned int fromNodeSize = fromNode->populationSize();
	unsigned int toNodeSize = toNode->populationSize();
	unsigned int fromIndex, toIndex;

	for (unsigned int i = 0; i < n; i++) {
		fromIndex = HierRNG::index(fromNodeSize);
		toIndex = HierRNG::index(toNodeSize);

		fromTranslate.isNull() ? oneWayMigrate(fromIndex, toIndex) :
			swap(fromIndex, toIndex);
	}

	toNode->evaluateFitnesses();
	if (!fromTranslate.isNull()) fromNode->evaluateFitnesses();
}
