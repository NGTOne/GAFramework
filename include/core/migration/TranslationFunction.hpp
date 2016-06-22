#include "../Genome.hpp"
#include <vector>
#include <tuple>
#pragma once

class TranslationFunction {
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
