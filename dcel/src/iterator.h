

#ifndef ITERATOR_H_
#define ITERATOR_H_

namespace ch
{
	template <typename T>
	class iterator
	{
	public:
		virtual void first() = 0;
		virtual void next()  = 0;
		virtual bool done()  = 0;
		virtual T current()  = 0;
		
		virtual ~iterator() {}
	};
}

#endif /* ITERATOR_H_ */
