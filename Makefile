CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x -fPIC -Wall
INCLUDE = -Iinclude -I/usr/local/include
EXAMPLEINCLUDE = -I/usr/local/include -Isrc/examples/include
STATICLIB = libs/libHierGA.a
MAJORVERSION = 2
MINORVERSION = 0

SHELL := /bin/bash
PLATFORM := $(shell uname -s)
ifeq ($(PLATFORM), Linux)
LIBNAME = libHierGA.so
else ifeq ($(PLATFORM), Darwin)
LIBNAME = libHierGA.dylib
endif

DYNAMICLIB = $(LIBNAME).$(MAJORVERSION).$(MINORVERSION)
LIBOBJS = $$(find obj -name *.o | grep -v examples)

ifeq ($(PLATFORM), Linux)
SHAREDLIB = -lHierGA
else ifeq ($(PLATFORM), Darwin)
SHAREDLIB = -L/usr/local/lib -lHierGA
endif

all: library

install: uninstall all-header
	sudo cp libs/$(LIBNAME) /usr/local/lib
	sudo chmod 0755 /usr/local/lib/$(LIBNAME)
	sudo mkdir /usr/local/include/libHierGA
	sudo cp -r include/* /usr/local/include/libHierGA
	if [[ "$$(uname -s)" == "Linux" ]]; then sudo ldconfig; fi

all-header:
	find include -name *.hpp | grep -v HierGA | sed 's/^include\///g' | \
		awk '{print "#include \"" $$1 "\""}' > include/HierGA.hpp
	echo "#pragma once" >> include/HierGA.hpp

uninstall:
	sudo rm -f /usr/local/lib/*libHierGA*
	sudo rm -rf /usr/local/include/*libHierGA*
	if [[ "$$(uname -s)" == "Linux" ]]; then sudo ldconfig; fi

library: obj-dir core objectives loci nodes endconditions exception \
		pop-formulae
	g++ -shared -o libs/$(LIBNAME) $(LIBOBJS)
	ar -cvq $(STATICLIB) $(LIBOBJS)

obj-dir:
	./compile-scripts/make-obj-dir.sh

core: builders
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Genome.cpp -o obj/core/Genome.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/FakeGenome.cpp -o obj/core/FakeGenome.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/GenomeTemplate.cpp -o obj/core/GenomeTemplate.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/ObjectiveFunction.cpp -o obj/core/ObjectiveFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/NestedObjective.cpp -o obj/core/NestedObjective.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/ToStringFunction.cpp -o obj/core/ToStringFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/PopulationFormula.cpp -o obj/core/PopulationFormula.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Apportionment.cpp -o obj/core/Apportionment.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/ApportionmentFunction.cpp -o obj/core/ApportionmentFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/AggregationFunction.cpp -o obj/core/AggregationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/PopulationNode.cpp -o obj/core/PopulationNode.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/EndCondition.cpp -o obj/core/EndCondition.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Locus.cpp -o obj/core/Locus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/TranslationFunction.cpp -o obj/core/migration/TranslationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/NullTranslationFunction.cpp -o obj/core/migration/NullTranslationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/MigratoryRelationship.cpp -o obj/core/migration/MigratoryRelationship.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/meta/MetaPopulationFactory.cpp -o obj/core/meta/MetaPopulationFactory.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/meta/BlanketResolver.cpp -o obj/core/meta/BlanketResolver.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/meta/MetaPopulationApportionment.cpp -o obj/core/meta/MetaPopulationApportionment.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/meta/MetaPopulationObjective.cpp -o obj/core/meta/MetaPopulationObjective.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/meta/MetaPopulationToString.cpp -o obj/core/meta/MetaPopulationToString.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/HierarchicalEA.cpp -o obj/core/HierarchicalEA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/gc/NodeGarbageCollector.cpp -o obj/core/gc/NodeGarbageCollector.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/HierRNG.cpp -o obj/core/gc/HierRNG.o

builders:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/builders/StructureBuilder.cpp -o obj/core/builders/StructureBuilder.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/builders/TreeBuilder.cpp -o obj/core/builders/TreeBuilder.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/builders/LatticeBuilder.cpp -o obj/core/builders/LatticeBuilder.o

objectives: apportionment-func aggregators
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/NoisyObjective.cpp -o obj/objectives/noisy/NoisyObjective.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/genetic-noise/GeneticNoiseSource.cpp -o obj/objectives/noisy/genetic-noise/GeneticNoiseSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/genetic-noise/NonNoisyGeneticSource.cpp -o obj/objectives/noisy/genetic-noise/NonNoisyGeneticSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/genetic-noise/UniformGeneticNoiseSource.cpp -o obj/objectives/noisy/genetic-noise/UniformGeneticNoiseSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/genetic-noise/BoundaryGeneticNoiseSource.cpp -o obj/objectives/noisy/genetic-noise/BoundaryGeneticNoiseSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/fitness-noise/FitnessNoiseSource.cpp -o obj/objectives/noisy/fitness-noise/FitnessNoiseSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/fitness-noise/NonNoisyFitnessSource.cpp -o obj/objectives/noisy/fitness-noise/NonNoisyFitnessSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/fitness-noise/GaussianFitnessNoiseSource.cpp -o obj/objectives/noisy/fitness-noise/GaussianFitnessNoiseSource.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/noisy/fitness-noise/ZeroingFitnessNoiseSource.cpp -o obj/objectives/noisy/fitness-noise/ZeroingFitnessNoiseSource.o

pop-formulae:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/pop-formulae/LocusMultiplierPopFormula.cpp -o obj/pop-formulae/LocusMultiplierPopFormula.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/pop-formulae/LocusBasePopFormula.cpp -o obj/pop-formulae/LocusBasePopFormula.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/pop-formulae/LocusExponentPopFormula.cpp -o obj/pop-formulae/LocusExponentPopFormula.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/pop-formulae/ConstructiveLocusCountPopFormula.cpp -o obj/pop-formulae/ConstructiveLocusCountPopFormula.o

loci:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/BoolLocus.cpp -o obj/loci/BoolLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/IntLocus.cpp -o obj/loci/IntLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/FloatLocus.cpp -o obj/loci/FloatLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/PopulationLocus.cpp -o obj/loci/PopulationLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/FakePopulationLocus.cpp -o obj/loci/FakePopulationLocus.o

aggregators:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/aggregators/AveragingAggregator.cpp -o obj/objectives/aggregators/AveragingAggregator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/aggregators/SummingAggregator.cpp -o obj/objectives/aggregators/SummingAggregators.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/aggregators/BestOfAggregator.cpp -o obj/objectives/aggregators/BestOfAggregator.o

apportionment-func:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/objectives/apportionment-func/SameFitnessApportionmentFunction.cpp -o obj/objectives/apportionment-func/SameFitnessApportionmentFunction.o

nodes: ea sa
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/NonOptimizingNode.cpp -o obj/nodes/NonOptimizingNode.o

ea: selections mutations crossovers systems
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/CrossoverOperation.cpp -o obj/nodes/EANode/CrossoverOperation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/MutationOperation.cpp -o obj/nodes/EANode/MutationOperation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/SelectionStrategy.cpp -o obj/nodes/EANode/SelectionStrategy.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/EvolutionarySystem.cpp -o obj/nodes/EANode/EvolutionarySystem.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/EANode.cpp -o obj/nodes/EANode/EANode.o

sa:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/SANode/TemperatureSchedule.cpp -o obj/nodes/SANode/TemperatureSchedule.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/SANode/schedules/LinearTempSchedule.cpp -o obj/nodes/SANode/schedules/LinearTempSchedule.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/SANode/schedules/ExponentialTempSchedule.cpp -o obj/nodes/SANode/schedules/ExponentialTempSchedule.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/SANode/SANode.cpp -o obj/nodes/SANode/SANode.o

selections:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/selections/RandomSelection.cpp -o obj/nodes/EANode/selections/RandomSelection.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/selections/TournamentSelection.cpp -o obj/nodes/EANode/selections/TournamentSelection.o

mutations:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/mutations/UniformMutation.cpp -o obj/nodes/EANode/mutations/UniformMutation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/mutations/BoundaryMutation.cpp -o obj/nodes/EANode/mutations/BoundaryMutation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/mutations/GaussianMutation.cpp -o obj/nodes/EANode/mutations/GaussianMutation.o

crossovers:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/crossovers/NPointCrossover.cpp -o obj/nodes/EANode/crossovers/NPointCrossover.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/crossovers/UniformCrossover.cpp -o obj/nodes/EANode/crossovers/UniformCrossover.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/crossovers/CutAndSpliceCrossover.cpp -o obj/nodes/EANode/crossovers/CutAndSpliceCrossover.o

systems:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/GA.cpp -o obj/nodes/EANode/systems/GA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/ES.cpp -o obj/nodes/EANode/systems/ES.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/SSGA.cpp -o obj/nodes/EANode/systems/SSGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/AccelSSGA.cpp -o obj/nodes/EANode/systems/AccelSSGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/niching/NichingStrategy.cpp -o obj/nodes/EANode/systems/niching/NichingStrategy.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/niching/Crowding.cpp -o obj/nodes/EANode/systems/niching/Crowding.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/ReplacingGA.cpp -o obj/nodes/EANode/systems/ReplacingGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/StrongIterativeReplacingGA.cpp -o obj/nodes/EANode/systems/StrongIterativeReplacingGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/nodes/EANode/systems/WeakIterativeReplacingGA.cpp -o obj/nodes/EANode/systems/WeakIterativeReplacingGA.o

endconditions:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/FitnessMatchEnd.cpp -o obj/endconditions/FitnessMatchEnd.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/MaxFitnessConvergenceEnd.cpp -o obj/endconditions/MaxFitnessConvergenceEnd.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/IterationCountEnd.cpp -o obj/endconditions/IterationCountEnd.o

exception:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/CustomMessageException.cpp -o obj/exception/CustomMessageException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/InvalidNodeException.cpp -o obj/exception/InvalidNodeException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NoEvolutionOrderException.cpp -o obj/exception/NoEvolutionOrderException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NodeAlreadyExistsException.cpp -o obj/exception/NodeAlreadyExistsException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NoNodesException.cpp -o obj/exception/NoNodesException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/MismatchedCountsException.cpp -o obj/exception/MismatchedCountsException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/ValueOutOfRangeException.cpp -o obj/exception/ValueOutOfRangeException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/ComponentNotPresentException.cpp -o obj/exception/ComponentNotPresentException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/InvalidBlanketException.cpp -o obj/exception/InvalidBlanketException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/CoevConstructionException.cpp -o obj/exception/CoevConstructionException.o

# Examples
examples: example-fitnesses
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/1max.cpp -o obj/examples/1max.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/Hier1max.cpp -o obj/examples/Hier1max.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/LongestFragment.cpp -o obj/examples/LongestFragment.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/HierLongestFragment.cpp -o obj/examples/HierLongestFragment.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/ApportioningHierLF.cpp -o obj/examples/ApportioningHierLF.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/MetaHierLF.cpp -o obj/examples/MetaHierLF.o
	$(CPPC) -o examples/1max obj/examples/1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/Hier1max obj/examples/Hier1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/LongestFragment obj/examples/LongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/HierLongestFragment obj/examples/HierLongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/ApportioningHierLF obj/examples/ApportioningHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/MetaHierLF obj/examples/MetaHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)

example-fitnesses:
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/1maxFitness.cpp -o obj/examples/fitnesses/1maxFitness.o
	$(CPPC) $(CPPFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/LongestFragmentFitness.cpp -o obj/examples/fitnesses/LongestFragmentFitness.o

hier3longestfragment:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3LongestFragment src/examples/Hier3LongestFragment/LongestFragmentFitness.cpp -o obj/examples/Hier3LongestFragment/LongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3LongestFragment src/examples/Hier3LongestFragment/HierLongestFragmentFitness.cpp -o obj/examples/Hier3LongestFragment/HierLongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3LongestFragment src/examples/Hier3LongestFragment/HierLongestFragment.cpp -o obj/examples/Hier3LongestFragment/HierLongestFragment.o
	$(CPPC) -o examples/Hier3LongestFragment obj/examples/Hier3LongestFragment/*.o $(SHAREDLIB)

hier3proprr:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropLF src/examples/Hier3PropLF/LongestFragmentFitness.cpp -o obj/examples/Hier3PropLF/LongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropLF src/examples/Hier3PropLF/HierLongestFragmentFitness.cpp -o obj/examples/Hier3PropLF/HierLongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropLF src/examples/Hier3PropLF/HierLongestFragment.cpp -o obj/examples/Hier3PropLF/HierLongestFragment.o
	$(CPPC) -o examples/Hier3PropLF obj/examples/Hier3PropLF/*.o $(SHAREDLIB)

clean:
	find obj -name *.o | xargs rm -f
	rm -f libs/*
	cd examples; ls | xargs rm -f
	rm -f /usr/libs/libHierGA.so*
