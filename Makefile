CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x -fPIC
INCLUDE = -Iinclude
STATICLIB = libs/libHierGA.a
MAJORVERSION = 1
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

examples: obj-dir 1-max hier1-max royalroad hierroyalroad hier3royalroad hier3proprr

library: obj-dir core selections mutations crossovers systems endconditions propagators exception
	g++ -shared -o libs/$(LIBNAME) $(LIBOBJS)
	ar -cvq $(STATICLIB) $(LIBOBJS)

obj-dir:
	./compile-scripts/make-obj-dir.sh

core:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Property.cpp -o obj/core/Property.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/PropertiesList.cpp -o obj/core/PropertiesList.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/CrossoverOperation.cpp -o obj/core/CrossoverOperation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/MutationOperation.cpp -o obj/core/MutationOperation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Genome.cpp -o obj/core/Genome.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Individual.cpp -o obj/core/Individual.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/GeneNode.cpp -o obj/core/GeneNode.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/LibraryNode.cpp -o obj/core/LibraryNode.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/SelectionStrategy.cpp -o obj/core/SelectionStrategy.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/EvolutionarySystem.cpp -o obj/core/EvolutionarySystem.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/EndCondition.cpp -o obj/core/EndCondition.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/PopulationNode.cpp -o obj/core/PopulationNode.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/NonEvolvingPopulationNode.cpp -o obj/core/NonEvolvingPopulationNode.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/TranslationFunction.cpp -o obj/core/migration/TranslationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/NullTranslationFunction.cpp -o obj/core/migration/NullTranslationFunction.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/migration/MigratoryRelationship.cpp -o obj/core/migration/MigratoryRelationship.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/HierarchicalEA.cpp -o obj/core/HierarchicalEA.o

selections: tournamentSelection

mutations: uniformMutation boundaryMutation

crossovers: nPointCrossover uniformCrossover cutAndSpliceCrossover

systems: ga es ssga rga annealer

endconditions: fitnessMatch

propagators: nonPropagator downPropagator apportioningPropagator

ga:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/GA.cpp -o obj/systems/GA.o

es:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/ES.cpp -o obj/systems/ES.o

ssga: niching
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/SSGA.cpp -o obj/systems/SSGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/AccelSSGA.cpp -o obj/systems/AccelSSGA.o

rga:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/ReplacingGA.cpp -o obj/systems/ReplacingGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/StrongIterativeReplacingGA.cpp -o obj/systems/StrongIterativeReplacingGA.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/WeakIterativeReplacingGA.cpp -o obj/systems/WeakIterativeReplacingGA.o

niching:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/systems/niching/Crowding.cpp -o obj/systems/niching/Crowding.o

tournamentSelection:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/selections/TournamentSelection.cpp -o obj/selections/TournamentSelection.o

uniformMutation:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/mutations/UniformMutation.cpp -o obj/mutations/UniformMutation.o

boundaryMutation:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/mutations/BoundaryMutation.cpp -o obj/mutations/BoundaryMutation.o

nPointCrossover:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/crossovers/NPointCrossover.cpp -o obj/crossovers/NPointCrossover.o

uniformCrossover:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/crossovers/UniformCrossover.cpp -o obj/crossovers/UniformCrossovers.o

cutAndSpliceCrossover:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/crossovers/CutAndSpliceCrossover.cpp -o obj/crossovers/CutAndSpliceCrossover.o

fitnessMatch:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/FitnessMatchEnd.cpp -o obj/endconditions/FitnessMatchEnd.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/endconditions/MaxFitnessConvergenceEnd.cpp -o obj/endconditions/MaxFitnessConvergenceEnd.o

nonPropagator:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/propagators/NonPropagator.cpp -o obj/propagators/NonPropagator.o

downPropagator:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/propagators/DownPropagator.cpp -o obj/propagators/DownPropagator.o

apportioningPropagator:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/propagators/ApportioningPropagator.cpp -o obj/propagators/ApportioningPropagator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/propagators/apportioning/AveragingPropagator.cpp -o obj/propagators/apportioning/AveragingPropagator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/propagators/apportioning/SummingPropagator.cpp -o obj/propagators/apportioning/SummingPropagator.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/propagators/apportioning/WeightedAveragePropagator.cpp -o obj/propagators/apportioning/WeightedAveragePropagator.o

annealer:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/secondary-pop-nodes/annealer/schedules/TemperatureSchedule.cpp -o obj/secondary-pop-nodes/annealer/schedules/TemperatureSchedule.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/secondary-pop-nodes/annealer/schedules/LinearTempSchedule.cpp -o obj/secondary-pop-nodes/annealer/schedules/LinearTempSchedule.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/secondary-pop-nodes/annealer/SimulatedAnnealer.cpp -o obj/secondary-pop-nodes/annealer/SimulatedAnnealer.o

exception:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/InvalidNodeException.cpp -o obj/exception/InvalidNodeException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NoEvolutionOrderException.cpp -o obj/exception/NoEvolutionOrder.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NodeAlreadyExistsException.cpp -o obj/exception/NodeAlreadyExistsException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/NoNodesException.cpp -o obj/exception/NoNodesException.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/exception/MismatchedCountsException.cpp -o obj/exception/MismatchedCountsException.o

# Examples
1-max:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/1max src/examples/1max/1maxFitness.cpp -o obj/examples/1max/1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/1max src/examples/1max/1max.cpp -o obj/examples/1max/1max.o
	$(CPPC) -o examples/1max obj/examples/1max/*.o $(SHAREDLIB)

hier1-max:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier1max src/examples/Hier1max/1maxFitness.cpp -o obj/examples/Hier1max/1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier1max src/examples/Hier1max/Hier1maxFitness.cpp -o obj/examples/Hier1max/Hier1maxFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier1max src/examples/Hier1max/Hier1max.cpp -o obj/examples/Hier1max/Hier1max.o
	$(CPPC) -o examples/Hier1max obj/examples/Hier1max/*.o $(SHAREDLIB)

royalroad:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/RoyalRoad src/examples/RoyalRoad/RoyalRoadFitness.cpp -o obj/examples/RoyalRoad/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/RoyalRoad src/examples/RoyalRoad/RoyalRoad.cpp -o obj/examples/RoyalRoad/RoyalRoad.o
	$(CPPC) -o examples/RoyalRoad obj/examples/RoyalRoad/*.o $(SHAREDLIB)

hierroyalroad:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/HierRoyalRoad src/examples/HierRoyalRoad/RoyalRoadFitness.cpp -o obj/examples/HierRoyalRoad/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/HierRoyalRoad src/examples/HierRoyalRoad/HierRoyalRoadFitness.cpp -o obj/examples/HierRoyalRoad/HierRoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/HierRoyalRoad src/examples/HierRoyalRoad/HierRoyalRoad.cpp -o obj/examples/HierRoyalRoad/HierRoyalRoad.o
	$(CPPC) -o examples/HierRoyalRoad obj/examples/HierRoyalRoad/*.o $(SHAREDLIB)

hier3royalroad:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3RoyalRoad src/examples/Hier3RoyalRoad/RoyalRoadFitness.cpp -o obj/examples/Hier3RoyalRoad/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3RoyalRoad src/examples/Hier3RoyalRoad/HierRoyalRoadFitness.cpp -o obj/examples/Hier3RoyalRoad/HierRoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3RoyalRoad src/examples/Hier3RoyalRoad/HierRoyalRoad.cpp -o obj/examples/Hier3RoyalRoad/HierRoyalRoad.o
	$(CPPC) -o examples/Hier3RoyalRoad obj/examples/Hier3RoyalRoad/*.o $(SHAREDLIB)

hier3proprr:
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropRR src/examples/Hier3PropRR/RoyalRoadFitness.cpp -o obj/examples/Hier3PropRR/RoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropRR src/examples/Hier3PropRR/HierRoyalRoadFitness.cpp -o obj/examples/Hier3PropRR/HierRoyalRoadFitness.o
	$(CPPC) $(CPPFLAGS) -Isrc/examples/Hier3PropRR src/examples/Hier3PropRR/HierRoyalRoad.cpp -o obj/examples/Hier3PropRR/HierRoyalRoad.o
	$(CPPC) -o examples/Hier3PropRR obj/examples/Hier3PropRR/*.o $(SHAREDLIB)

clean:
	find obj -name *.o | xargs rm -f
	rm -f libs/*
	cd examples; ls | xargs rm -f
	rm -f /usr/libs/libHierGA.so*
