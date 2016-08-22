#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class SphereFitness : public ObjectiveFunction {
	private:

	protected:

	public:
	SphereFitness();
	float checkFitness(Genome * genome);
};

class SphereToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(Genome * genome);
};
