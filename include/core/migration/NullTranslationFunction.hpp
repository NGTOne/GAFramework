#include "../Genome.hpp"
#include "TranslationFunction.hpp"
#pragma once

class NullTranslationFunction : public TranslationFunction {
	private:

	protected:
	virtual std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	> translate(Genome * target);

	public:
	virtual Genome * createTranslatedGenome(
		Genome * target,
		std::string targetNode
	);
	virtual bool isNull();
};
