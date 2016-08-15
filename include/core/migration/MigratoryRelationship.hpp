#ifndef CORE_MIGRATION_MigratoryRelationship
#define CORE_MIGRATION_MigratoryRelationship

#include "../PopulationNode.hpp"
#include "TranslationFunction.hpp"
#include <random>

class MigratoryRelationship {
	private:

	protected:
	PopulationNode * fromNode;
	PopulationNode * toNode;
	TranslationFunction toTranslate;
	TranslationFunction fromTranslate;
	unsigned int n;

	void init(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		unsigned int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	void swap(unsigned int fromNodeIndex, unsigned int toNodeIndex);
	void oneWayMigrate(
		unsigned int fromNodeIndex,
		unsigned int toNodeIndex
	);

	public:
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		unsigned int n
	);
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		unsigned int n,
		TranslationFunction toTranslate
	);
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		unsigned int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	void migrate();
};

#endif
