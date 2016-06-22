#include "core/migration/MigratoryRelationship.hpp"
#include "core/migration/NullTranslationFunction.hpp"
#include "core/PopulationNode.hpp"
#include <random>
#include <chrono>

using namespace std;

MigratoryRelationship::MigratoryRelationship(
	PopulationNode * fromNode,
	PopulationNode * toNode,
	int n
) {
	init(fromNode, toNode, n, TranslationFunction(), TranslationFunction());
}

MigratoryRelationship::MigratoryRelationship(
	PopulationNode * fromNode,
	PopulationNode * toNode,
	int n,
	TranslationFunction toTranslate
) {
	init(fromNode, toNode, n, toTranslate, NullTranslationFunction());
}

MigratoryRelationship::MigratoryRelationship(
	PopulationNode * fromNode,
	PopulationNode * toNode,
	int n,
	TranslationFunction toTranslate,
	TranslationFunction fromTranslate
) {
	init(fromNode, toNode, n, toTranslate, fromTranslate);
}

void MigratoryRelationship::init(
	PopulationNode * fromNode,
	PopulationNode * toNode,
	int n,
	TranslationFunction toTranslate,
	TranslationFunction fromTranslate
) {
	this->fromNode = fromNode;
	this->toNode = toNode;
	this->n = n;
	this->toTranslate = toTranslate;
	this->fromTranslate = fromTranslate;
	generator = mt19937(chrono::system_clock::now().time_since_epoch().count());
}

void MigratoryRelationship::swap(int fromNodeIndex, int toNodeIndex) {
	Genome * fromNodeInsert,
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

void MigratoryRelationship::oneWayMigrate(int fromNodeIndex, int toNodeIndex) {
	Genome * original, * insert;

	original = fromNode->getIndex(fromNodeIndex);
	insert = toTranslate.createTranslatedGenome(
		original,
		this->toNode->name()
	);
	toNode->insert(toNodeIndex, insert);
}

void MigratoryRelationship::migrate() {
	int fromNodeSize = fromNode->populationSize();
	int toNodeSize = toNode->populationSize();
	int fromIndex, toIndex;
	uniform_int_distribution<int> fromNodeDist(0, fromNodeSize);
	uniform_int_distribution<int> toNodeDist(0, toNodeSize);

	for (int i = 0; i < n; i++) {
		fromIndex = fromNodeDist(generator);
		toIndex = toNodeDist(generator);

		fromTranslate.isNull() ? oneWayMigrate(fromIndex, toIndex) :
			swap(fromIndex, toIndex);
	}

	toNode->evaluateFitnesses();
	if (!fromTranslate.isNull()) fromNode->evaluateFitnesses();
}
