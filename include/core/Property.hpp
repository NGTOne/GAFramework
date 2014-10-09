#pragma once

/*
* These two simple classes allow the use of different object types as
* properties. They can then be disposed of using their built-in destructors
* as necessary.
*
* The PropertyBase class is used to allow grouping of different types of
* the Property template class.
*/

class PropertyBase {
	private:

	protected:

	public:
	virtual ~PropertyBase()=0;

	virtual PropertyBase * makeCopy()=0;
	virtual void * getProperty()=0;
};

template <class T>
class Property : public PropertyBase {
	private:
	T * myProperty;

	protected:

	public:
	Property();
	Property(T * newProperty);

	~Property();

	void setProperty(T * newProperty);
	T * getProperty();
	
	Property<T> * makeCopy();
};
