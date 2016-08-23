#include "nodes/EANode/mutations/CovarianceMatrixSelfAdaptiveMutation.hpp"
#include <math.h>

CovarianceMatrixSelfAdaptiveMutation::CovarianceMatrixSelfAdaptiveMutation(
	unsigned int mu,
	unsigned int lambda
) : AdaptiveRealValueMutation() {
	this->mu = mu;
	this->lambda = lambda;
}

CovarianceMatrixSelfAdaptiveMutation::CovarianceMatrixSelfAdaptiveMutation(
	unsigned int mu,
	unsigned int lambda,
	double tau,
	double tauC
) : AdaptiveRealValueMutation() {
	this->mu = mu;
	this->lambda = lambda;
	this->tau = tau;
	this->tauC = tauC;
	this->tausCalculated = true;
}

void CovarianceMatrixSelfAdaptiveMutation::calculateTaus(Genome* initial) {
	unsigned int n = initial->genomeLength();
	this->tau = 1/sqrt(2 * n);
	this->tauC = 1 + n * (n + 1)/(2 * this->mu);
	this->tausCalculated = true;
}

void CovarianceMatrixSelfAdaptiveMutation::calculateProperGenomeLengths(
	Genome* initial
) {
	this->initialGenomeLength = initial->genomeLength();
	this->targetGenomeLength = initial->genomeLength() + 1;
}

Genome* CovarianceMatrixSelfAdaptiveMutation::addStdDevs(Genome* target) {
	std::vector<Gene*> newGenes = target->getGenomeCopy();
	newGenes.push_back(this->stdDevLocus->getGene(1));

	if (this->stdDevIndices.empty())
		stdDevIndices.push_back(target->genomeLength());

	return new Genome(newGenes, target->getSpeciesNode());
}

void CovarianceMatrixSelfAdaptiveMutation::otherSetupSteps(Genome* initial) {
	unsigned int n = initial->genomeLength();
	this->C = Eigen::MatrixXd::Identity(n, n);
}
