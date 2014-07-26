#include <libGAFramework/GAFramework.hpp>
#include <string>
#pragma once

class RoyalRoadToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
