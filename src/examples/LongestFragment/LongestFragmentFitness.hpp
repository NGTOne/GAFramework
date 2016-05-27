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
