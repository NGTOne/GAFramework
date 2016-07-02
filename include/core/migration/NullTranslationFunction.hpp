#include "../Genome.hpp"
#include "../GenomeTemplate.hpp"
#include "TranslationFunction.hpp"
#pragma once

class NullTranslationFunction : public TranslationFunction {
	private:

	protected:
	virtual GenomeTemplate translate(Genome * target);

	public:
	virtual Genome * createTranslatedGenome(
		Genome * target,
		std::string targetNode
	);
	virtual bool isNull();
};
