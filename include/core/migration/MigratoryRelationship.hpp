#include "../PopulationNode.hpp"
#include "TranslationFunction.hpp"
#pragma once

class MigratoryRelationship {
	private:

	protected:
	PopulationNode * fromNode;
	PopulationNode * toNode;
	TranslationFunction toTranslate;
	TranslationFunction fromTranslate;

	public:
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		TranslationFunction toTranslate
	);
	MigratoryRelationship(
		PopulationNode * fromNode,
		PopulationNode * toNode,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	void migrate();
};
