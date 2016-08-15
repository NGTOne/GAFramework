#ifndef NODES_EANODE_MUTATIONS_UniformMutation
#define NODES_EANODE_MUTATIONS_UniformMutation

#include "../MutationOperation.hpp"

/*
* The uniform mutation operator randomly decides whether or not to mutate
* a given allele along the genome, and then sets it to a random value from
* the allele's range.
*/

class UniformMutation : public MutationOperation {
	private:

	protected:
	virtual Gene* newLocusValue(Gene* current);

	public:
	UniformMutation();
	UniformMutation(double mutationRate);
};

#endif
