#include "core/FitnessSource.hpp"

FitnessSource::FitnessSource() {
	this->source = boost::variant<ObjectiveFunction*, Genome*>(
		(Genome*)NULL
	);
}

FitnessSource::FitnessSource(
	boost::variant<ObjectiveFunction*, Genome*> source
) {
	this->source = source;
}

const boost::variant<
	ObjectiveFunction*,
	Genome*
> FitnessSource::getSource() const {
	return this->source;
}

bool FitnessSource::operator==(const FitnessSource& rhs) const {
	return rhs.getSource() == this->source;
}

bool FitnessSource::operator!=(const FitnessSource& rhs) const {
	return !(*this == rhs);
}
