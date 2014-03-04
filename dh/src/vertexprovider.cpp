
#include "vertexprovider.h"
#include <cassert>

namespace ch
{
	template <typename T>
	vertexprovider<T>::vertexprovider( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ )
		: dataholder<T>( data, coordPad_, diffSize_, vertNum_ )
	{
	}

	template <typename T>
	vertexprovider<T>::~vertexprovider()
	{
	}

	template <typename T>
	vertexdata<T> vertexprovider<T>::operator[]( size_t i ) const
	{
		assert( i < this->vertNum );
		size_t first = i * this->diffSize / sizeof(T);
		return vertexdata<T>(	this->dataPtr[first + 0 + 0*this->coordPad],
								this->dataPtr[first + 1 + 1*this->coordPad],
								this->dataPtr[first + 2 + 2*this->coordPad] );
	}

	template <typename T>
	size_t vertexprovider<T>::size() const
	{
		return this->vertNum;
	}


	template <typename T>
	dataholder<T>& getDataHolder( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ )
	{
		static vertexprovider<T> vp( data, coordPad_, diffSize_, vertNum_ );
		return vp;
	}
}
