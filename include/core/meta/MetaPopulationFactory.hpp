#include "../PopulationNode.hpp"
#include "../Apportionment.hpp"
#include "../ObjectiveFunction.hpp"
#include "../ToStringFunction.hpp"
#include <vector>
#include <tuple>

class MetaPopulationFactory {
	private:

	protected:
	static std::vector<PopulationNode*> getAllHierarchicalNodes(
		std::vector<PopulationNode*> nodes
	);

	static bool isCompleteBlanket(std::vector<PopulationNode*> nodes);
	static bool isValidBlanket(
		PopulationNode * topNode,
		std::vector<PopulationNode*> nodes
	);

	public:
	static PopulationNode * createMeta(
		PopulationNode * metaNode,
		std::vector<ObjectiveFunction *> flattenedObjectives,
		ToStringFunction * flattenedToString,
		PopulationNode * topNode,
		std::tuple<
			ApportionmentFunction *,
			AggregationFunction *
		> topNodeApportionment,
		std::vector<std::tuple<
			PopulationNode *,
			ApportionmentFunction *,
			AggregationFunction *
		>> secondaryNodes
	);
};
