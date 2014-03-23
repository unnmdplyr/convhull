
#include "dataholder.h"

namespace ch
{
	template <typename U>
	vertexdata<U>::vertexdata( U x_, U y_, U z_ )
		: x(x_)
		, y(y_)
		, z(z_) {}

	template <typename U>
	bool vertexdata<U>::operator==( const vertexdata<U>& rhs ) const
	{
		return  fabs(x - rhs.x) < epsilon
			&&  fabs(y - rhs.y) < epsilon
			&&  fabs(z - rhs.z) < epsilon;
	}

	template <typename U>
	bool vertexdata<U>::operator!=( const vertexdata<U>& rhs ) const
	{
		return  !operator==(rhs);
	}


	template <typename T>
	dataholder<T>::dataholder( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ )
		: dataPtr(data)
		, coordPad(coordPad_)
		, diffSize(diffSize_)
		, vertNum(vertNum_)
	{
		assert( diffSize > 2  &&  "Diff size cannot be smaller than 3." );
	}

	template <typename T>
	dataholder<T>::~dataholder()
	{
		dataPtr = nullptr;
	}
}
