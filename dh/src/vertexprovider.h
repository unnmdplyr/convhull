

#ifndef VERTEXPROVIDER_H_
#define VERTEXPROVIDER_H_

#include "dataholder.h"

namespace ch
{
	template <typename T>
	class vertexprovider final : public dataholder<T>
	{
	public:
		vertexprovider( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ );
		~vertexprovider();

		virtual vertexdata<T> operator[]( size_t i ) const override;
		virtual size_t size() const override;
	};

	template <typename T>
	std::unique_ptr<dataholder<T>> getDataHolder( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ );
}

#endif	/*	VERTEXPROVIDER_H_	*/
