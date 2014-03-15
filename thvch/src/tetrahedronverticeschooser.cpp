
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
	}
}
