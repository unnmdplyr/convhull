
#include "vertexprovider.h"

namespace ch
{
	template <typename T>
	vertexprovider<T>::vertexprovider( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ )
		: dataholder<T>( data, coordPad_, diffSize_, vertNum_ )
	{
	}

	template <typename T>
	dataholder<T>::vertexdata<T> vertexprovider<T>::operator[]( size_t i ) const
	{
		assert( i < this->vertNum );
		size_t first = i * this->diffSize;
		return dataholder<T>::template vertexdata<T>(
											this->dataPtr[first + 0*sizeof(T) + 0*this->coordPad],
											this->dataPtr[first + 1*sizeof(T) + 1*this->coordPad],
											this->dataPtr[first + 2*sizeof(T) + 2*this->coordPad] );
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