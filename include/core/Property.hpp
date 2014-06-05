//Lets us create whatever properties we like, and use their built-in
//destructors when we don't need them
#pragma once

class PropertyBase {}; //So we can group them

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
};
