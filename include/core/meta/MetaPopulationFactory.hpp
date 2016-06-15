#include "../PopulationNode.hpp"
#include "../Apportionment.hpp"
#include "../ObjectiveFunction.hpp"
#include <vector>
#include <tuple>

class MetaPopulationFactory {
	private:

	protected:

	public:
	static PopulationNode * createMeta(
		PopulationNode * metaNode,
		std::vector<ObjectiveFunction *> flattenedObjectives,
		PopulationNode * topNode,
		Apportionment * topNodeApportionment,
		std::vector<std::tuple<
			PopulationNode *,
			Apportionment *
		>> secondaryNodes
	);
};
