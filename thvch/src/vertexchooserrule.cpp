
#include "vertexchooserrule.h"

namespace ch
{
	template <typename T>
	vertexchooserrule<T>::vertexchooserrule()
	{
	}

	template <typename T>
	vertexchooserrule<T>::~vertexchooserrule()
	{
	}


	template <typename T>
	vertexchooserrule1st<T>::vertexchooserrule1st() : vertexchooserrule()
	{
	}

	template <typename T>
	vertexchooserrule1st<T>::~vertexchooserrule1st()
	{
	}

	template <typename T>
	void vertexchooserrule1st<T>::chooseVertex( const dataholder<T>& dh, vector<vid_t>& vertices ) const
	{
	}

}