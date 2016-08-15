#ifndef CORE_MIGRATION_TranslationFunction
#define CORE_MIGRATION_TranslationFunction

#include "../Genome.hpp"
#include "../GenomeTemplate.hpp"
#include <vector>

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

#endif
