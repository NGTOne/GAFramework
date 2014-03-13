#include <sstream>

class OneMaxFitness : FitnessFunction {
	private:

	protected:

	public:
	int checkFitness(GenePool pools[], int indexes[], int genomeLength) {
		int total = 0;

		for (int i = 0; i < genomeLength; i++) {
			total += (int)pools[i].getIndex(indexes[i]);
		}

		return total;
	}

	string toString(GenePool pools[], int indexes[], int genomeLength) {
		string returnString = "";
		stringstream ss;


		for (int i = 0; i < genomeLength; i++) {
			ss << (int)pools[i].getIndex(indexes[i]);
		}

		returnString = ss.str();

		return returnString;
	}
}
