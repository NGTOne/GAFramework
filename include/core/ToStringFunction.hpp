#include <string>
#include "Genome.hpp"
#pragma once

class ToStringFunction {
	private:

	protected:

	public:
	virtual ~ToStringFunction();
	virtual std::string toString(Genome * genome)=0;
};
