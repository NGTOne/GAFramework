#include "PopulationNode.hpp"
#include "Apportionment.hpp"
#include "ObjectiveFunction.hpp"
#include <vector>
#include <tuple>

class MetaPopulationFactory {
	private:

	protected:

	public:
	static PopulationNode * createMeta(
		PopulationNode * metaNode,
		PopulationNode * topNode,
		ObjectiveFunction * topObjective,
		std::vector<std::tuple<
			PopulationNode *,
			Apportionment *
		>> secondaryNodes
	);
};
