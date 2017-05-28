#ifndef CORE_FitnessSource
#define CORE_FitnessSource

#include <boost/variant/variant.hpp>
#include "eval/ObjectiveFunction.hpp"
#include "Genome.hpp"

class ObjectiveFunction;
class Genome;

class FitnessSource {
	private:

	protected:
	boost::variant<ObjectiveFunction*, Genome*> source;

	public:
	FitnessSource();
	FitnessSource(boost::variant<ObjectiveFunction*, Genome*> source);
	const boost::variant<ObjectiveFunction*, Genome*> getSource() const;

	bool operator==(const FitnessSource& rhs) const;
	bool operator!=(const FitnessSource& rhs) const;
};

#endif
