#include "core/Property.hpp"
#include <cstdlib>

using namespace std;

template <class T> Property<T>::Property() {
	myProperty = NULL;
}

template <class T> Property<T>::Property(T * newProperty) {
	myProperty = newProperty;
}

template <class T> Property<T>::~Property() {
	if (myProperty != NULL) {
		delete(myProperty);
	}
}

template <class T> void Property<T>::setProperty(T * newProperty) {
	if (myProperty != NULL) {
		delete(myProperty);
	}

	myProperty = newProperty;
}

template <class T> T * Property<T>::getProperty() {
	return myProperty;
}
