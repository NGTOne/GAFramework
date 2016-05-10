#include "../Genome.hpp"
#include "TranslationFunction.hpp"
#pragma once

class NullTranslationFunction : public TranslationFunction {
	private:

	protected:

	public:
	virtual Genome * translate(Genome * target);
	virtual bool isNull();
};
