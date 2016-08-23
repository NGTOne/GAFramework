#include "nodes/EANode/systems/ES/CMSA_ES.hpp"
#include "core/utils/HierRNG.hpp"
#include <math.h>
#include <unsupported/Eigen/MatrixFunctions>

CMSA_ES::CMSAMutation::CMSAMutation(
	unsigned int lambda
) : AdaptiveRealValueMutation() {
	this->lambda = lambda;
}

CMSA_ES::CMSAMutation::CMSAMutation(
	unsigned int lambda,
	double tau,
	double tauC
) : AdaptiveRealValueMutation() {
	this->lambda = lambda;
	this->tau = tau;
	this->tauC = tauC;
	this->tausCalculated = true;
}

void CMSA_ES::CMSAMutation::calculateTaus(Genome* initial) {
	unsigned int n = initial->genomeLength();
	this->tau = 1/sqrt(2 * n);
	this->tauC = 1 + n * (n + 1)/(2 * this->mu);
	this->tausCalculated = true;
}

void CMSA_ES::CMSAMutation::calculateProperGenomeLengths(
	Genome* initial
) {
	this->initialGenomeLength = initial->genomeLength();
	this->targetGenomeLength = initial->genomeLength() + 1;
}

Genome* CMSA_ES::CMSAMutation::addStdDevs(Genome* target) {
	std::vector<Gene*> newGenes = target->getGenomeCopy();
	newGenes.push_back(this->stdDevLocus->getGene(1));

	if (this->stdDevIndices.empty())
		stdDevIndices.push_back(target->genomeLength());

	return new Genome(newGenes, target->getSpeciesNode());
}

void CMSA_ES::CMSAMutation::otherSetupSteps(Genome* initial) {
	unsigned int n = initial->genomeLength();
	this->C = Eigen::MatrixXd::Identity(n, n);
}

void CMSA_ES::CMSAMutation::setMu(unsigned int mu) {
	this->mu = mu;
}

void CMSA_ES::CMSAMutation::calculateAverages(std::vector<Genome*> population) {
	unsigned int n = population[0]->genomeLength();
	double sigmaSum;
	std::vector<double> xSums(n, 0);

	for (unsigned int i = 0; i < population.size(); i++) {
		// Since the stdDevs haven't necessarily been set up yet, we
		// need to account for that
		sigmaSum += !this->stdDevIndices.empty() ?
			population[i]->getIndex<double>(this->stdDevIndices[0]) :
			1;

		std::vector<Gene*> genes = population[i]->getGenome();
		for (unsigned int k = 0; k < n; k++)
			xSums[k] += genes[k]->getIndex();
	}

	this->sigmaAvg = sigmaSum/this->mu;

	this->xAvg.clear();
	for (unsigned int i = 0; i < xSums.size(); i++)
		this->xAvg.push_back(xSums[i]/this->mu);

	if (!this->skCollection.empty()) {
		Eigen::MatrixXd SAvg = Eigen::MatrixXd::Zero(
			this->initialGenomeLength,
			this->initialGenomeLength
		);

		for (unsigned int i = 0; i < this->skCollection.size(); i++) {
			Eigen::VectorXd sk = this->skCollection[i];
			SAvg += sk * sk.transpose();
		}

		SAvg /= this->lambda;
		this->skCollection.clear();
		this->C = (1 - 1/this->tauC) * this->C + SAvg/this->tauC;
	}
}

Genome* CMSA_ES::CMSAMutation::mutateProper(Genome* target) {
	std::vector<Gene*> newGenes = target->getGenomeCopy();

	Gene* stdDevGene = newGenes[this->stdDevIndices[0]];
	double sigmaK = this->sigmaAvg
		* exp(HierRNG::gaussian(0, 1) * this->tau);
	newGenes[this->stdDevIndices[0]] = stdDevGene->copy(sigmaK);
	delete(stdDevGene);

	Eigen::VectorXd R(this->initialGenomeLength);
	for (unsigned int i = 0; i < this->initialGenomeLength; i++)
		R[i] = HierRNG::gaussian(0, 1);

	Eigen::VectorXd sk = this->C.sqrt() * R;
	Eigen::VectorXd zk = sigmaK * sk;

	for (unsigned int i = 0; i < this->initialGenomeLength; i++) {
		Gene* originalGene = newGenes[i];
		newGenes[i] = originalGene->copy(this->xAvg[i] + zk[i]);
		delete(originalGene);
	}

	this->skCollection.push_back(sk);
	return new Genome(newGenes, target->getSpeciesNode());
}
