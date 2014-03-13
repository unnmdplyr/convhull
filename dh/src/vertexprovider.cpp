
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
		size_t first = i * this->diffSize;

		const char* x = reinterpret_cast<const char*>(this->dataPtr)  +  first  +  0 * this->coordPad  +  0 * sizeof(T);
		const T* xT = reinterpret_cast<const T*>(x);

//		const char* y = reinterpret_cast<const char*>(this->dataPtr)  +  first  +  1 * this->coordPad  +  1 * sizeof(T);
		const char* y = x  +  1 * this->coordPad  +  1 * sizeof(T);
		const T* yT = reinterpret_cast<const T*>(y);

//		const char* z = reinterpret_cast<const char*>(this->dataPtr)  +  first  +  2 * this->coordPad  +  2 * sizeof(T);
		const char* z = y  +  1 * this->coordPad  +  1 * sizeof(T);
		const T* zT = reinterpret_cast<const T*>(z);

		return vertexdata<T>( *xT, *yT, *zT );
	}

	template <typename T>
	size_t vertexprovider<T>::size() const
	{
		return this->vertNum;
	}


	template <typename T>
	std::unique_ptr<dataholder<T>> getDataHolder( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ )
	{
		return std::unique_ptr<dataholder<T>>( new vertexprovider<T>( data, coordPad_, diffSize_, vertNum_ ) );
	}
}
