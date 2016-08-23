#include "nodes/EANode/systems/ES/CMSA_ES.hpp"

CMSA_ES::CMSA_ES(
	unsigned int lambda
) : MuCommaLambdaES(new CMSAMutation(lambda), lambda) {}

CMSA_ES::CMSA_ES(
	unsigned int lambda,
	double tau,
	double tauC
) : MuCommaLambdaES(new CMSAMutation(lambda, tau, tauC), lambda) {}
