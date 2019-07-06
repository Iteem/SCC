#ifndef BASEPROPERTY_INCLUDED
#define BASEPROPERTY_INCLUDED

class BaseProperty
{
	public:
		BaseProperty();
		virtual ~BaseProperty();
};

template <typename T>
class Property
{
	public:
		Property( const T& value );
		virtual ~Property();

		T data;
};

template <typename T>
Property<T>::Property( const T& value ) :
	data( value )
{
}

template <typename T>
Property<T>::~Property()
{
}


#endif // BASEPROPERTY_INCLUDED
