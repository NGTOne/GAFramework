#include "../Genome.hpp"
#pragma once

class TranslationFunction {
	private:

	protected:

	public:
	virtual Genome * translate(Genome * target);
	virtual bool isNull();
};
