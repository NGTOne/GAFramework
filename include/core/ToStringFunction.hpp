#include <string>
#include "Genome.hpp"
#pragma once

class ToStringFunction {
	private:

	protected:

	public:
	virtual std::string toString(Genome * genome)=0;
};
