

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <vector>

//	---- only to printout
#include <iostream>
using std::cout;
using std::endl;
//	---- only to printout


namespace ch
{
	template <typename T>
	class nop_deleter final
	{
	public:
		typedef void result_type;
		typedef T argument_type;
		result_type operator()(argument_type) const
		{
		}
	};

	template <typename T>
	class single_deleter final
	{
	public:
		typedef void result_type;
		typedef T argument_type;
		result_type operator()(argument_type a) const
		{
			delete a;
		}
	};


	template <	typename T,
				template <typename> class D = single_deleter >
	class collection final
	{
	public:
		collection();
		collection(std::initializer_list<T>);
		~collection();

		void push_back( T&& element );
		void push_back( const T& element );
		size_t size() const;
		const T& operator[](size_t i) const;

	private:
		std::vector<T> elements;
		const D<T> deleter;

		char padding[8 - sizeof(deleter) % 8];
		static_assert(	sizeof(padding) < 8
						, "Padding is bigger in class collection than it is expected." );
	};
}


#endif
