



#ifndef VERTEXCHOOSERRULE_H_
#define VERTEXCHOOSERRULE_H_

#include <vector>
#include "dcel_intf.h"

namespace ch
{
	template <typename T> class dataholder;

	template <typename T>
	class vertexchooserrule
	{
	public:
		vertexchooserrule();
		virtual ~vertexchooserrule();

		virtual void chooseVertex( const dataholder<T>& dh, std::vector<vid_t>& vertices ) const = 0;
	};

	template <typename T>
	class vertexchooserrule1st final : public vertexchooserrule<T>
	{
	public:
		vertexchooserrule1st();
		virtual ~vertexchooserrule1st();
		vertexchooserrule1st( const vertexchooserrule1st& rhs ) = delete;
		vertexchooserrule1st& operator=( const vertexchooserrule1st& rhs ) = delete;
		vertexchooserrule1st& operator=( vertexchooserrule1st&& rhs ) = delete;

		void chooseVertex( const dataholder<T>& dh, std::vector<vid_t>& vertices ) const override;
	};

	template <typename T>
	class vertexchooserrule2nd final : public vertexchooserrule<T>
	{
	public:
		vertexchooserrule2nd();
		virtual ~vertexchooserrule2nd();
		vertexchooserrule2nd( const vertexchooserrule2nd& rhs ) = delete;
		vertexchooserrule2nd& operator=( const vertexchooserrule2nd& rhs ) = delete;
		vertexchooserrule2nd& operator=( vertexchooserrule2nd&& rhs ) = delete;

		void chooseVertex( const dataholder<T>& dh, std::vector<vid_t>& vertices ) const override;
	};


}


#endif
