CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x -fPIC
INCLUDE = -Iinclude
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

examples: obj-dir 1-max hier1-max longestfragment hierlongestfragment hier3longestfragment hier3proprr

library: obj-dir core loci nodes endconditions exception
	g++ -shared -o libs/$(LIBNAME) $(LIBOBJS)
	ar -cvq $(STATICLIB) $(LIBOBJS)

obj-dir:
	./compile-scripts/make-obj-dir.sh

core:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Genome.cpp -o obj/core/Genome.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/PopulationNode.cpp -o obj/core/PopulationNode.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/EndCondition.cpp -o obj/core/EndCondition.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Locus.cpp -o obj/core/Locus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/TranslationFunction.cpp -o obj/core/migration/TranslationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/NullTranslationFunction.cpp -o obj/core/migration/NullTranslationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/MigratoryRelationship.cpp -o obj/core/migration/MigratoryRelationship.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/HierarchicalEA.cpp -o obj/core/HierarchicalEA.o

loci:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/BoolLocus.cpp -o obj/loci/BoolLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/IntLocus.cpp -o obj/loci/IntLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/FloatLocus.cpp -o obj/loci/FloatLocus.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/loci/PopulationLocus.cpp -o obj/loci/PopulationLocus.o

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

# Examples
1-max:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/1max src/examples/1max/1maxFitness.cpp -o obj/examples/1max/1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/1max src/examples/1max/1max.cpp -o obj/examples/1max/1max.o
	$(CPPC) -o examples/1max obj/examples/1max/*.o $(SHAREDLIB)

hier1-max:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier1max src/examples/Hier1max/Hier1maxFitness.cpp -o obj/examples/Hier1max/Hier1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier1max src/examples/Hier1max/Hier1max.cpp -o obj/examples/Hier1max/Hier1max.o
	$(CPPC) -o examples/Hier1max obj/examples/Hier1max/*.o $(SHAREDLIB)

longestfragment:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/LongestFragment src/examples/LongestFragment/LongestFragmentFitness.cpp -o obj/examples/LongestFragment/LongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/LongestFragment src/examples/LongestFragment/LongestFragment.cpp -o obj/examples/LongestFragment/LongestFragment.o
	$(CPPC) -o examples/LongestFragment obj/examples/LongestFragment/*.o $(SHAREDLIB)

hierlongestfragment:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/HierLongestFragment src/examples/HierLongestFragment/LongestFragmentFitness.cpp -o obj/examples/HierLongestFragment/LongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/HierLongestFragment src/examples/HierLongestFragment/HierLongestFragmentFitness.cpp -o obj/examples/HierLongestFragment/HierLongestFragmentFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/HierLongestFragment src/examples/HierLongestFragment/HierLongestFragment.cpp -o obj/examples/HierLongestFragment/HierLongestFragment.o
	$(CPPC) -o examples/HierLongestFragment obj/examples/HierLongestFragment/*.o $(SHAREDLIB)

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
