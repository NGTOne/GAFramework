#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class HierLongestFragmentFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	HierLongestFragmentFitness();
	int checkFitness(Genome * target);
};

class HierLongestFragmentToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(Genome * target);
};
