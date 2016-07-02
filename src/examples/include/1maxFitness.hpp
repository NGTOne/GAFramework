#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class OneMaxFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	OneMaxFitness();
	float checkFitness(Genome * genome);
};

class OneMaxToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(Genome * genome);
};
