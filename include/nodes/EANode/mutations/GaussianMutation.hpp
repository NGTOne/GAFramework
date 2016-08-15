#ifndef NODES_EANODE_MUTATIONS_GaussianMutation
#define NODES_EANODE_MUTATIONS_GaussianMutation

#include "../MutationOperation.hpp"

/*
* Gaussian mutation changes the value of the allele by randomly generating
* a number on the normal distribution and adding it to the allele's value
*/

class GaussianMutation : public MutationOperation {
	private:

	protected:
	bool endReflection;
	double mean;
	double stdDev;

	virtual Gene* newLocusValue(Gene* current);
	void init(double mean, double stdDev, bool endReflection);

	public:
	GaussianMutation(double stdDev);
	GaussianMutation(double mean, double stdDev);
	GaussianMutation(double mean, double stdDev, bool endReflection);
	GaussianMutation(double mean, double stdDev, double mutationRate);
	GaussianMutation(
		double mean,
		double stdDev,
		bool endReflection,
		double mutationRate
	);
};

#endif
