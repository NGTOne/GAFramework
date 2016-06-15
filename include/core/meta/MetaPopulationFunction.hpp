#include "../ObjectiveFunction.hpp"
#pragma once

class MetaPopulationFunction : public ObjectiveFunction {
	private:

	protected:

	public:
	virtual ObjectiveFunction * getFunction()=0;
};
