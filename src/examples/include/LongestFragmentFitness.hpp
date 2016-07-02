#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class LongestFragmentFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	LongestFragmentFitness();
	float checkFitness(Genome * target);
};

class LongestFragmentToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(Genome * target);
};

class LongestFragmentApportionment : public ApportionmentFunction {
	private:

	protected:

	public:
	float apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientStartIndex,
		std::vector<unsigned int> relevantRecipientIndices,
		float providerFitness
	);
};
