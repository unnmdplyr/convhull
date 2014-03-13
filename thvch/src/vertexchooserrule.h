



#ifndef VERTEXCHOOSERRULE_H_
#define VERTEXCHOOSERRULE_H_


namespace ch
{
	template <typename T>
	class vertexchooserrule
	{
	public:
		vertexchooserrule();
		virtual ~vertexchooserrule();

		virtual void chooseVertex( const dataholder<T>& dh, vector<vid_t>& vertices ) const = 0;
	};

	template <typename T>
	class vertexchooserrule1st final : public vertexchooserrule<T>
	{
	public:
		vertexchooserrule1st();
		virtual ~vertexchooserrule1st();

		void chooseVertex( const dataholder<T>& dh, vector<vid_t>& vertices ) const override;
	};

}


#endif
