

#include <cassert>
#include <type_traits>

#include "collection.h"

//	---- only to printout
#include <iostream>
using std::cout;
using std::endl;
//	---- only to printout


namespace ch
{
	template <typename T, template <typename> class D>
	collection<T,D>::collection()
		: elements()
		, deleter( D<T>() )
	{
	}

	template <typename T, template <typename> class D>
	collection<T,D>::collection( std::initializer_list<T> args )
		: elements(args)
		, deleter( D<T>() )
	{
	}

	template <typename T, template <typename> class D>
	collection<T,D>::~collection()
	{
		if ( !std::is_pointer<T>::value )
			return;

		for ( auto i : elements )
			deleter( i );
	}


	template <typename T, template <typename> class D>
	void collection<T,D>::push_back( T&& element )
	{
		elements.push_back( element );
	}

	template <typename T, template <typename> class D>
	void collection<T,D>::push_back( const T& element )
	{
		elements.push_back( element );
	}

	template <typename T, template <typename> class D>
	size_t collection<T,D>::size() const
	{
		return elements.size();
	}

	template <typename T, template <typename> class D>
	const T& collection<T,D>::operator[](size_t i) const
	{
		assert( elements.size() > i );
		return elements[i];
	}
}
