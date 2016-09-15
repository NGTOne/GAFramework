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

class LongestFragmentToString : public HierarchicalToString {
	private:

	protected:

	public:
	LongestFragmentToString(
		HierarchicalToString::mode printMode
			= HierarchicalToString::flatten
	);
	std::string stringifySegment(std::vector<Gene*> segment);
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
