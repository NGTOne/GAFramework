#include "core/Property.hpp"
#include <cstdlib>

using namespace std;

PropertyBase::~PropertyBase() {}

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

template <class T> Property<T> * Property<T>::makeCopy() {
	T * newValue = new T(myProperty);

	Property<T> * newProperty = new Property<T>(newValue);

	return newProperty;
}

// int specialization
template <> Property<int>::Property() {
	myProperty=NULL;
}

template <> Property<int>::Property(int * newProperty) {
	myProperty = (int*)malloc(sizeof(int));

	*myProperty = *newProperty;
}

template <> Property<int>::~Property() {
	if (myProperty != NULL) {
		free(myProperty);
	}
}

template <> void Property<int>::setProperty(int * newProperty) {
	if (myProperty == NULL) {
		myProperty = (int*)malloc(sizeof(int));
	}

	*myProperty = *newProperty;
}

template <> Property<int> * Property<int>::makeCopy() {
	int newValue;
	newValue = *myProperty;

	Property<int> * newProperty = new Property<int>(&newValue);

	return newProperty;
}
