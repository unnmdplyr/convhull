

#ifndef DATAHOLDER_H_
#define DATAHOLDER_H_

#include <cstddef>
#include <cmath>
#include <limits>

namespace ch
{
	template <typename U>
	class vertexdata final
	{
	public:
		static constexpr U epsilon = static_cast<U>(1.1) * std::numeric_limits<U>::epsilon();

		vertexdata( U x_, U y_, U z_ );

		bool operator==( const vertexdata& rhs ) const;
		bool operator!=( const vertexdata& rhs ) const;

		U x;
		U y;
		U z;
	};

	template <typename T>
	class dataholder
	{
	public:
		dataholder( const T* data, size_t coordPad_, size_t diffSize_, size_t vertNum_ );
		virtual ~dataholder();

		dataholder( const dataholder& rhs ) = delete;
		dataholder( dataholder&& rhs ) = delete;
		dataholder& operator=( const dataholder& rhs ) = delete;
		dataholder& operator=( dataholder&& rhs ) = delete;

		virtual vertexdata<T> operator[]( size_t i ) const = 0;
		virtual size_t size() const = 0;

	protected:
		const T* dataPtr;		///<	pointer to the first element
		const size_t coordPad;	///<	padding between coordinates in bytes
		const size_t diffSize;	///<	difference between begin address of two consecutive vertices in bytes
		const size_t vertNum;	///<	number of vertices
	};
}


#endif	/*	DATAHOLDER_H_	*/
