#include "../PopulationNode.hpp"
#include "TranslationFunction.hpp"
#include <random>
#pragma once

class MigratoryRelationship {
	private:

	protected:
	PopulationNode * fromNode;
	PopulationNode * toNode;
	TranslationFunction toTranslate;
	TranslationFunction fromTranslate;
	int n;

	std::mt19937 generator;

	void init(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	void swap(int fromNodeIndex, int toNodeIndex);
	void oneWayMigrate(int fromNodeIndex, int toNodeIndex);

	public:
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		int n
	);
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		int n,
		TranslationFunction toTranslate
	);
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	void migrate();
};
