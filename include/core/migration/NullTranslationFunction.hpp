#include "../Individual.hpp"
#include "TranslationFunction.hpp"
#pragma once

class NullTranslationFunction : public TranslationFunction {
	private:

	protected:

	public:
	virtual Individual * translate(Individual * target);
	virtual bool isNull();
};
