#ifndef LOCI_FakePopulationLocus
#define LOCI_FakePopulationLocus

#include "PopulationLocus.hpp"
#include "../core/Genome.hpp"
#include <vector>
#include <string>

// This "locus" type is useful for apportionment, because it allows us
// to selectively and transparently replace a genome with one of our choosing

class FakePopulationLocus: public PopulationLocus {
	private:

	protected:
	Genome* target;
	bool fakeGenome;

	public:
	FakePopulationLocus(
		Genome* target,
		PopulationLocus* original,
		bool fakeGenome
	);
	FakePopulationLocus(Genome target, PopulationLocus* original);
	FakePopulationLocus(FakePopulationLocus* target);
	~FakePopulationLocus();

	bool isFake();
	bool genomeIsFake();

	std::string toString();
	std::string flatten(Gene* index);

	boost::any getIndex(Gene* index);
};

#endif
