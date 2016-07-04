#include "objectives/noisy/scramblers/NonScrambler.hpp"

NonScrambler::NonScrambler() : GeneScrambler() {};

Genome NonScrambler::scramble(Genome * target) {
	return Genome(target);
}
