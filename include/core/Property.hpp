#pragma once

//Lets us create whatever properties we like, and use their built-in
//destructors when we don't need them.
class PropertyBase {
	private:

	protected:

	public:
	virtual ~PropertyBase()=0;

	virtual PropertyBase * makeCopy()=0;
	virtual void * getProperty()=0;
}; //So we can group them

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
