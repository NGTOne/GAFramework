#include "FitnessFunction.h"
#include <string>

class OneMaxFitness : FitnessFunction {
	private:

	protected:

	public:
	int checkFitness(GenePool pools[], int indexes[], int genomeLength);

	std::string toString(GenePool pools[], int indexes[], int genomeLength);
};
