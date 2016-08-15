#ifndef NODES_EANODE_MutationOperation
#define NODES_EANODE_MutationOperation

#include "../../core/Genome.hpp"
#include "../../core/GenomeTemplate.hpp"
#include "../../core/EABehaviourObject.hpp"
#include <random>
#include <string>

/*
* This abstract class allows the creation of any mutation operator that is
* desired.
*/

class MutationOperation : public EABehaviourObject {
	private:

	protected:
        double mutationRate;

	virtual Gene* newLocusValue(Gene* current)=0;
	void init(double mutationRate);

	public:
	MutationOperation();
	MutationOperation(double mutationRate);
	virtual ~MutationOperation();

	virtual Genome* mutate(Genome* initialGenome);
	GenomeTemplate mutate(GenomeTemplate initial);

	std::string toString();
};

#endif
