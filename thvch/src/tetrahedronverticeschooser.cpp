
#include "tetrahedronverticeschooser.h"

namespace ch
{
	template <typename T>
	tetrahedronverticeschooser<T>::tetrahedronverticeschooser( const dataholder<T>& dh ) : vertexchooser<T>(dh)
	{
	}

	template <typename T>
	tetrahedronverticeschooser<T>::~tetrahedronverticeschooser()
	{
	}

	template <typename T>
	void tetrahedronverticeschooser<T>::chooseVertices(	const collection<vertexchooserrule<T>*>& ruleCollection,
														std::vector<vid_t>& vertices ) const
	{
		for ( size_t i=0; i < ruleCollection.size(); ++i )
		{
			ruleCollection[i]->chooseVertex( this->dh, vertices );

			if ( vertices.size() < i+1 )	//	this round didn't find any proper vertex indices
				return;
		}
	}
}
