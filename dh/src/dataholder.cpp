
#include "dataholder.h"

namespace ch
{
	template <typename U>
	vertexdata<U>::vertexdata( U x_, U y_, U z_ )
		: x(x_)
		, y(y_)
		, z(z_) {}

	template <typename T>
	dataholder<T>::dataholder( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ )
		: dataPtr(data)
		, coordPad(coordPad_)
		, diffSize(diffSize_)
		, vertNum(vertNum_)
	{
	}

	template <typename T>
	dataholder<T>::~dataholder()
	{
		dataPtr = nullptr;
	}
}
