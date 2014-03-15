


#ifndef VERTEXCHOOSER_H_
#define VERTEXCHOOSER_H_

#include "collection_impl.h"

namespace ch
{
	template <typename T> class vertexchooserrule;
	template <typename T> class dataholder;

	template <typename T>
	class vertexchooser
	{
	public:
		vertexchooser( const dataholder<T>& dh );
		virtual ~vertexchooser();

		virtual void chooseVertices(const collection<vertexchooserrule<T>*>& ruleCollection,
									std::vector<vid_t>& vertices ) const = 0;
	protected:
		const dataholder<T>& dh;
	};
}


#endif
