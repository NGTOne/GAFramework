#include "objectives/noisy/scramblers/NonScrambler.hpp"

NonScrambler::NonScrambler() : GeneScrambler(NULL) {};

Genome NonScrambler::scramble(Genome * target) {
	return Genome(target);
}
