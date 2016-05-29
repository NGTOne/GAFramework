#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class LongestFragmentFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	LongestFragmentFitness();
	int checkFitness(Genome * target);
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
	int apportionFitness(
		Genome * recipient,
		Genome * provider,
		int providerFitness
	);
};
