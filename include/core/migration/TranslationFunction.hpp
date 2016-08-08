#include "../Genome.hpp"
#include "../GenomeTemplate.hpp"
#include <vector>
#pragma once

class TranslationFunction {
	private:

	protected:
	virtual GenomeTemplate translate(GenomeTemplate target);

	public:
	virtual Genome* createTranslatedGenome(
		Genome* target,
		std::string targetNode
	);
	virtual bool isNull();
};
