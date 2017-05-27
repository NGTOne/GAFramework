#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class OneMaxFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	OneMaxFitness();
	Fitness checkFitness(Genome* genome);
};

class OneMaxToString : public HierarchicalToString {
	private:

	protected:

	public:
	OneMaxToString(
		HierarchicalToString::mode printMode
			= HierarchicalToString::flatten
	);
	std::string stringifySegment(std::vector<Gene*> segment);
};
