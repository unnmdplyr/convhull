
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
	vertexchooserrule1st<T>::vertexchooserrule1st() : vertexchooserrule<T>()
	{
	}

	template <typename T>
	vertexchooserrule1st<T>::~vertexchooserrule1st()
	{
	}

	//	First rule:	get the first vertex
	template <typename T>
	void vertexchooserrule1st<T>::chooseVertex( const dataholder<T>& /*dh*/, std::vector<vid_t>& vertices ) const
	{
		//	The main part must make sure that more than 4 vertices reside in the dataholder.
		vertices.push_back( 0 );
	}


	template <typename T>
	vertexchooserrule2nd<T>::vertexchooserrule2nd() : vertexchooserrule<T>()
	{
	}

	template <typename T>
	vertexchooserrule2nd<T>::~vertexchooserrule2nd()
	{
	}

	//	Second rule:	get the first vertex which doesn't reside at the same place in the 3D space as the first one
	template <typename T>
	void vertexchooserrule2nd<T>::chooseVertex( const dataholder<T>& dh, std::vector<vid_t>& vertices ) const
	{
		for ( size_t i = 1; i < dh.size(); ++i )
		{
			if ( dh[0] == dh[i] )
				continue;

			vertices.push_back(i);
			break;
		}
	}


}
