#include "gc/PopulationNodeDeallocator.hpp"
#include "core/PopulationNode.hpp"
#include "core/ApportionmentFunction.hpp"
#include "core/AggregationFunction.hpp"
#include "core/Apportionment.hpp"
#include "core/NestedObjective.hpp"
#include <set>

PopulationNodeDeallocator::PopulationNodeDeallocator() {}
PopulationNodeDeallocator::~PopulationNodeDeallocator() {}

bool PopulationNodeDeallocator::canDeleteNode(PopulationNode * node) {
	return true;
}

void PopulationNodeDeallocator::deleteNodes() {
	std::set<Locus*> loci;
	std::set<EndCondition*> conditions;
	std::set<ObjectiveFunction*> objectives;
	std::set<ApportionmentFunction*> apportionments;
	std::set<AggregationFunction*> aggregators;
	std::set<ToStringFunction*> toStrings;

	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		PopulationNode * temp = this->nodes[i];

		std::set<Locus*> tempLoci = temp->getLoci();
		loci.insert(tempLoci.begin(), tempLoci.end());

		vector<EndCondition*> tempConditions = temp->getConditions();
		conditions.insert(
			tempConditions.begin(),
			tempConditions.end()
		);

		vector<ObjectiveFunction*> tempObjectives =
			temp->getObjectives();
		objectives.insert(
			tempObjectives.begin(),
			tempObjectives.end()
		);

		for (unsigned int k = 0; k < tempObjectives.size(); k++) {
			if (tempObjectives[k]->isApportioning()) {
				Apportionment * temp =
					(Apportionment*)tempObjectives[k];
				apportionments.insert(
					temp->getApportionmentFunction()
				);
				aggregators.insert(
					temp->getAggregationFunction()
				);
			}

			if (tempObjectives[k]->isNested()) {
				NestedObjective * temp =
					(NestedObjective*)tempObjectives[k];
				std::vector<ObjectiveFunction*> inner =
					temp->getInner();
				objectives.insert(inner.begin(), inner.end());
			}
		}

		toStrings.insert(temp->getToString());
	}

	this->clearSet<Locus*>(loci);
	this->clearSet<EndCondition*>(conditions);
	this->clearSet<ObjectiveFunction*>(objectives);
	this->clearSet<ApportionmentFunction*>(apportionments);
	this->clearSet<AggregationFunction*>(aggregators);
	this->clearSet<ToStringFunction*>(toStrings);
}
