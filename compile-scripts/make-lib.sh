#!/bin/bash -ex

CPPC=g++
CPPFLAGS="-c -g -std=gnu++0x -fPIC -Wall -Werror -pedantic-errors"
INCLUDE="-Iinclude -I/usr/local/include"

if [[ $(uname -s) == "Linux" ]]
then
	LIBNAME="libHierGA.so"
	EIGEN="-I/usr/include/eigen3"
elif [[ $(uname -s) == "Darwin" ]]
then
	LIBNAME="libHierGA.dylib"
	EIGEN="-I/usr/local/include/eigen3"
fi

for codeFile in $(find src -name *.cpp | grep -v examples)
do
	outFile=${codeFile/src\//obj\/}
	outFile=${outFile/\.cpp/\.o}

	$CPPC $CPPFLAGS $INCLUDE $EIGEN $codeFile -o $outFile
done

$CPPC -shared -o libs/$LIBNAME $(find obj -name *.o | grep -v examples)
