CXX = g++
CXXFLAGS = -c -g -std=gnu++0x -fPIC -Wall -Werror -pedantic-errors
OBJ = obj
SRC = src

SHELL := /bin/bash
PLATFORM := $(shell uname -s)

ifeq ($(PLATFORM), Linux)
SHAREDLIB = -lHierGA
LIBNAME = libHierGA.so
EIGEN = -I/usr/include/eigen3
else ifeq ($(PLATFORM), Darwin)
SHAREDLIB = -L/usr/local/lib -lHierGA
LIBNAME = libHierGA.dylib
EIGEN = -I/usr/local/include/eigen3
endif

INCLUDE = -Iinclude -I/usr/local/include $(EIGEN)
EXAMPLEINCLUDE = -I/usr/local/include -Isrc/examples/include $(EIGEN)
LIB_SOURCE := $(shell find src -name *.cpp | grep -v examples)
LIB_OBJS := $(patsubst src/%.cpp,obj/%.o,$(LIB_SOURCE))

all: library

install: uninstall all-header
	sudo cp libs/$(LIBNAME) /usr/local/lib
	sudo chmod 0755 /usr/local/lib/$(LIBNAME)
	sudo mkdir /usr/local/include/libHierGA
	sudo cp -r include/* /usr/local/include/libHierGA
	if [[ "$$(uname -s)" == "Linux" ]]; then sudo ldconfig; fi

# This is useful for importing the lib, so we autogenerate it
all-header:
	echo "#ifndef HIERGA" > include/HierGA.hpp
	echo "#define HIERGA" >> include/HierGA.hpp
	find include -name *.hpp | grep -v HierGA | sed 's/^include\///g' | \
		awk '{print "#include \"" $$1 "\""}' >> include/HierGA.hpp
	echo "#endif" >> include/HierGA.hpp

uninstall:
	sudo rm -f /usr/local/lib/*libHierGA*
	sudo rm -rf /usr/local/include/*libHierGA*
	if [[ "$$(uname -s)" == "Linux" ]]; then sudo ldconfig; fi

obj/%.o: src/%.cpp
	# We want to create the directory in /obj if it doesn't exist already
	mkdir -p $$(echo $@ | sed 's/\/[^\/]\+\.o//g')
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $<

library: all-header $(LIB_OBJS)
	$(CXX) -shared -o libs/$(LIBNAME) $(LIB_OBJS)

# Examples
# TODO: Refactor this lot of crap
examples: example-fitnesses
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/1max.cpp -o obj/examples/1max.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/Sphere.cpp -o obj/examples/Sphere.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/Hier1max.cpp -o obj/examples/Hier1max.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/LongestFragment.cpp -o obj/examples/LongestFragment.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/HierLongestFragment.cpp -o obj/examples/HierLongestFragment.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/ApportioningHierLF.cpp -o obj/examples/ApportioningHierLF.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/MetaHierLF.cpp -o obj/examples/MetaHierLF.o
	$(CXX) -o examples/1max obj/examples/1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CXX) -o examples/Sphere obj/examples/Sphere.o obj/examples/fitnesses/SphereFitness.o $(SHAREDLIB)
	$(CXX) -o examples/Hier1max obj/examples/Hier1max.o obj/examples/fitnesses/1maxFitness.o $(SHAREDLIB)
	$(CXX) -o examples/LongestFragment obj/examples/LongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CXX) -o examples/HierLongestFragment obj/examples/HierLongestFragment.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CXX) -o examples/ApportioningHierLF obj/examples/ApportioningHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)
	$(CXX) -o examples/MetaHierLF obj/examples/MetaHierLF.o obj/examples/fitnesses/LongestFragmentFitness.o $(SHAREDLIB)

example-fitnesses:
	mkdir -p obj/examples/fitnesses
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/1maxFitness.cpp -o obj/examples/fitnesses/1maxFitness.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/SphereFitness.cpp -o obj/examples/fitnesses/SphereFitness.o
	$(CXX) $(CXXFLAGS) $(EXAMPLEINCLUDE) src/examples/fitnesses/LongestFragmentFitness.cpp -o obj/examples/fitnesses/LongestFragmentFitness.o

clean:
	find obj -name *.o | xargs rm -f
	rm -f libs/*
	cd examples; ls | xargs rm -f
	rm -f /usr/libs/libHierGA.so*
