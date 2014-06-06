#include "core/Property.hpp"
#include <cstdlib>

using namespace std;

template <class T> Property<T>::Property() {
	myProperty = NULL;
}

template <class T> Property<T>::Property(T * newProperty) {
	myProperty = newProperty;
}

template <> Property<int>::Property(int * newProperty) {
	myProperty = newProperty;
}

template <class T> Property<T>::~Property() {
	if (myProperty != NULL) {
		delete(myProperty);
	}
}

template <> Property<int>::~Property() {
	if (myProperty != NULL) {
		free(myProperty);
	}
}

template <class T> void Property<T>::setProperty(T * newProperty) {
	if (myProperty != NULL) {
		delete(myProperty);
	}

	myProperty = newProperty;
}

template <> void Property<int>::setProperty(int * newProperty) {
	if (myProperty != NULL) {
		free(myProperty);
	}

	myProperty = newProperty;
}

template <class T> T * Property<T>::getProperty() {
	return myProperty;
}
