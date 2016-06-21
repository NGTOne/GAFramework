CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x -fPIC -Wall
INCLUDE = -Iinclude -I/usr/local/include
STATICLIB = libs/libHierGA.a
MAJORVERSION = 2
MINORVERSION = 0
LIBNAME = libHierGA.so
DYNAMICLIB = $(LIBNAME).$(MAJORVERSION).$(MINORVERSION)
LIBOBJS = $$(find obj -name *.o | grep -v examples)

SHAREDLIB = -lHierGA

info:
	@echo "Usage:"
	@echo "make library: Rebuilds the library from scratch"
	@echo "make install: Installs the compiled library and header files into /usr"
	@echo "make examples: Produces a series of examples GAs and hierarchical GAs using the shared library. Requires make install to be run first."
	@echo "make uninstall: Uninstalls the library and header files"
	@echo "make clean: Cleans up all compiled binaries and object files"
	@echo "make core: Produces the object files for the \"core\" components"
	@echo "make selections: Produces the object files for the selection strategies"
	@echo "make mutations: Produces the object files for the mutation operators"
	@echo "make crossovers: Produces the object files for the crossover operators"
	@echo ""
	@echo "Any GA/HGA needs at least core, and one component from each of selections, mutations, and crossovers in order to function."

all: library

install:
	sudo cp libs/$(LIBNAME) /usr/lib
	sudo chmod 0755 /usr/lib/$(LIBNAME)
	sudo mkdir /usr/include/libHierGA
	sudo cp -r include/* /usr/include/libHierGA
	sudo ldconfig

uninstall:
	sudo rm /usr/lib/*libHierGA*
	sudo rm -r /usr/include/*libHierGA*
	sudo ldconfig

library: obj-dir core loci aggregators apportionment-func \
		nodes endconditions exception gc
	g++ -shared -o libs/$(LIBNAME) $(LIBOBJS)
	ar -cvq $(STATICLIB) $(LIBOBJS)

obj-dir:
	./compile-scripts/make-obj-dir.sh

core:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Genome.cpp -o obj/core/Genome.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/ObjectiveFunction.cpp -o obj/core/ObjectiveFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/ToStringFunction.cpp -o obj/core/ToStringFunction.o
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
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/gc/NodeDeallocator.cpp -o obj/core/gc/NodeDeallocator.o

gc:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/gc/PopulationNodeDeallocator.cpp -o obj/gc/PopulationNodeDeallocator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/gc/NonOptimizingNodeDeallocator.cpp -o obj/gc/NonOptimizingNodeDeallocator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/gc/EANodeDeallocator.cpp -o obj/gc/EANodeDeallocator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/gc/SANodeDeallocator.cpp -o obj/gc/SANodeDeallocator.o

loci:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/BoolLocus.cpp -o obj/loci/BoolLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/IntLocus.cpp -o obj/loci/IntLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/FloatLocus.cpp -o obj/loci/FloatLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/PopulationLocus.cpp -o obj/loci/PopulationLocus.o

aggregators:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/aggregators/AveragingAggregator.cpp -o obj/aggregators/AveragingAggregator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/aggregators/SummingAggregator.cpp -o obj/aggregators/SummingAggregators.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/aggregators/BestOfAggregator.cpp -o obj/aggregators/BestOfAggregator.o

apportionment-func:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/apportionment-func/SameFitnessApportionmentFunction.cpp -o obj/apportionment-func/SameFitnessApportionmentFunction.o

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
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/selections/RandomSelection.cpp -o obj/selections/RandomSelection.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/selections/TournamentSelection.cpp -o obj/selections/TournamentSelection.o

mutations:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/mutations/UniformMutation.cpp -o obj/mutations/UniformMutation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/mutations/BoundaryMutation.cpp -o obj/mutations/BoundaryMutation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/mutations/GaussianMutation.cpp -o obj/mutations/GaussianMutation.o

crossovers:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/crossovers/NPointCrossover.cpp -o obj/crossovers/NPointCrossover.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/crossovers/UniformCrossover.cpp -o obj/crossovers/UniformCrossovers.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/crossovers/CutAndSpliceCrossover.cpp -o obj/crossovers/CutAndSpliceCrossover.o

systems:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/GA.cpp -o obj/systems/GA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/ES.cpp -o obj/systems/ES.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/SSGA.cpp -o obj/systems/SSGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/AccelSSGA.cpp -o obj/systems/AccelSSGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/niching/NichingStrategy.cpp -o obj/systems/niching/NichingStrategy.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/niching/Crowding.cpp -o obj/systems/niching/Crowding.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/ReplacingGA.cpp -o obj/systems/ReplacingGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/StrongIterativeReplacingGA.cpp -o obj/systems/StrongIterativeReplacingGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/WeakIterativeReplacingGA.cpp -o obj/systems/WeakIterativeReplacingGA.o

endconditions:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/FitnessMatchEnd.cpp -o obj/endconditions/FitnessMatchEnd.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/MaxFitnessConvergenceEnd.cpp -o obj/endconditions/MaxFitnessConvergenceEnd.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/IterationCountEnd.cpp -o obj/endconditions/IterationCountEnd.o

exception:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/InvalidNodeException.cpp -o obj/exception/InvalidNodeException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NoEvolutionOrderException.cpp -o obj/exception/NoEvolutionOrderException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NodeAlreadyExistsException.cpp -o obj/exception/NodeAlreadyExistsException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NoNodesException.cpp -o obj/exception/NoNodesException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/MismatchedCountsException.cpp -o obj/exception/MismatchedCountsException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/ValueOutOfRangeException.cpp -o obj/exception/ValueOutOfRangeException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/ComponentNotPresentException.cpp -o obj/exception/ComponentNotPresentException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/InvalidBlanketException.cpp -o obj/exception/InvalidBlanketException.o

# Examples
examples: example-fitnesses
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/1max.cpp -o obj/examples/1max.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/Hier1max.cpp -o obj/examples/Hier1max.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/LongestFragment.cpp -o obj/examples/LongestFragment.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/HierLongestFragment.cpp -o obj/examples/HierLongestFragment.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/ApportioningHierLF.cpp -o obj/examples/ApportioningHierLF.o
	$(CPPC) -o examples/1max obj/examples/1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/Hier1max obj/examples/Hier1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/LongestFragment obj/examples/LongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/HierLongestFragment obj/examples/HierLongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CPPC) -o examples/ApportioningHierLF obj/examples/ApportioningHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)

example-fitnesses:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/fitnesses/1maxFitness.cpp -o obj/examples/fitnesses/1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/include src/examples/fitnesses/LongestFragmentFitness.cpp -o obj/examples/fitnesses/LongestFragmentFitness.o

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
