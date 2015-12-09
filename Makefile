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

examples: 1-max hier1-max royalroad hierroyalroad hier3royalroad hier3proprr

library: core selections mutations crossovers generations endconditions propagators
	g++ -shared -o libs/$(LIBNAME) $(LIBOBJS)
	ar -cvq $(STATICLIB) $(LIBOBJS)

core:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Property.cpp -o obj/core/Property.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/PropertiesList.cpp -o obj/core/PropertiesList.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/CrossoverOperation.cpp -o obj/core/CrossoverOperation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/MutationOperation.cpp -o obj/core/MutationOperation.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Genome.cpp -o obj/core/Genome.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/Individual.cpp -o obj/core/Individual.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/GenePool.cpp -o obj/core/GenePool.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/NonHierarchicalGenePool.cpp -o obj/core/NonHierarchicalGenePool.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/SelectionStrategy.cpp -o obj/core/SelectionStrategy.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/GenerationModel.cpp -o obj/core/GenerationModel.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/EndCondition.cpp -o obj/core/EndCondition.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/core/HierarchicalGenePool.cpp -o obj/core/HierarchicalGenePool.o

selections: tournamentSelection

mutations: uniformMutation boundaryMutation

crossovers: nPointCrossover uniformCrossover cutAndSpliceCrossover

generations: ga es ssga rga

endconditions: fitnessMatch

propagators: nonPropagator downPropagator apportioningPropagator

ga:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/generations/GAGeneration.cpp -o obj/generations/GAGeneration.o

es:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/generations/ESGeneration.cpp -o obj/generations/ESGeneration.o

ssga: niching
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/generations/SSGAGeneration.cpp -o obj/generations/SSGAGeneration.o

rga:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/generations/ReplacingGAGeneration.cpp -o obj/generations/ReplacingGAGeneration.o

niching:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/generations/niching/Crowding.cpp -o obj/generations/niching/Crowding.o

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
