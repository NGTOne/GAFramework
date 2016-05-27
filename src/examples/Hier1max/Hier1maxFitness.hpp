#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class HierOneMaxFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	HierOneMaxFitness();
	int checkFitness(Genome * genome);
};

class HierOneMaxToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(Genome * genome);
};
