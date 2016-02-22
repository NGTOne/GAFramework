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
	Individual * fromNodeInsert,
		* toNodeInsert,
		* fromNodeOriginal,
		* toNodeOriginal;

	fromNodeOriginal = (Individual*)fromNode->getIndex(fromNodeIndex);
	toNodeOriginal = (Individual*)toNode->getIndex(toNodeIndex);

	toNodeInsert = toTranslate.translate(fromNodeOriginal);
	fromNodeInsert = fromTranslate.translate(toNodeOriginal);

	toNode->insert(toNodeIndex, toNodeInsert);
	fromNode->insert(fromNodeIndex, fromNodeInsert);
}

void MigratoryRelationship::oneWayMigrate(int fromNodeIndex, int toNodeIndex) {
	Individual * original, * insert;

	original = (Individual*) fromNode->getIndex(fromNodeIndex);
	insert = toTranslate.translate(original);
	toNode->insert(toNodeIndex, insert);
}

void MigratoryRelationship::migrate() {
	int fromNodeSize = fromNode->getPopulationSize();
	int toNodeSize = toNode->getPopulationSize();
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
