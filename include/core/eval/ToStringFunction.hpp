#ifndef CORE_ToStringFunction
#define CORE_ToStringFunction

#include <string>
#include "../Genome.hpp"
#include "../EABehaviourObject.hpp"

class ToStringFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~ToStringFunction();
	virtual std::string toString(Genome * genome)=0;
	virtual bool isNested();
};

#endif
