


#ifndef TETRAHEDRONVERTICESCHOOSER_H_
#define TETRAHEDRONVERTICESCHOOSER_H_

#include "vertexchooser.h"

namespace ch
{
	template <typename T>
	class tetrahedronverticeschooser final : public vertexchooser<T>
	{
	public:
		tetrahedronverticeschooser( const dataholder<T>& dh );
		~tetrahedronverticeschooser();

		void chooseVertices(const collection<vertexchooserrule>& ruleCollection,
							vector<vid_t>& vertices ) const override;
	};
}


#endif
