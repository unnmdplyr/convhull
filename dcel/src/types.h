
#ifndef TYPES_H_
#define TYPES_H_

#include <iosfwd>
#include <limits>
#include <set>
#include <utility>


namespace ch
{

	///	\brief	Vertex type
	typedef std::size_t vid_t;

	///	\brief	Half edge ID type
	typedef std::pair< vid_t, vid_t > heid_t;

	///	\brief	Face ID type
	typedef std::size_t fid_t;

	//==========================================================================

	static const heid_t INVALID_EDGE_ID = heid_t(
											std::numeric_limits<vid_t>::max(),
											std::numeric_limits<vid_t>::max() );

	static const fid_t	INVALID_FACE_ID = 0;//std::numeric_limits<fid_t>::max();

	//==========================================================================

	class vertex
	{
	public:
		///	The id of the vertex.
		vid_t	id;

		///	\brief	Id of an arbitrary half-edge that has this vertex as
		///			its origin.
		heid_t	incidentEdge;
		
		explicit vertex( vid_t vid, heid_t heid = INVALID_EDGE_ID ) : id(vid), incidentEdge( heid )
		{
		}
	};
	
	//--------------------------------------------------------------------------

	class vertex_less : public std::binary_function< const vertex&, const vertex&, bool >
	{
	public:
		result_type operator() (first_argument_type v1, second_argument_type v2) const
		{
			return v1.id < v2.id;
		}
	};

	//==========================================================================

	class face
	{
	public:
		///	The id of the face.
		fid_t	id;

		///	\brief	Id of some half-edge on outer boundary of the face.
		heid_t	outerComponent;
		
		explicit face( fid_t faceId, heid_t outerComp = INVALID_EDGE_ID ) : id( faceId ),
																			outerComponent( outerComp )
		{
		}
	};

	//--------------------------------------------------------------------------

	class face_less : public std::binary_function< const face&, const face&, bool >
	{
	public:
		result_type operator() (first_argument_type f1, second_argument_type f2) const
		{
			return f1.id < f2.id;
		}
	};

	//==========================================================================

	///	\brief	Stores an half edge and its related data
	///	\details	The half edges reside at right side of the face, if we take
	///				a look to the face from its outer side. The half edges runs
	///				in CCW direction on the boundary of the face.
	class half_edge
	{
	public:
		///	The id of the half edge.
		heid_t	id;

		///	\brief	Pointer to the previous edge on the boundary of
		///			incidentFace
		heid_t	prev;

		///	\brief	Pointer to the next edge on the boundary of incidentFace
		heid_t	next;

		///	\brief	A pointer to the face that it bounds.
		fid_t	incidentFace;

		explicit half_edge( vid_t f, vid_t s,
							heid_t prevHe = INVALID_EDGE_ID,
							heid_t nextHe = INVALID_EDGE_ID,
							fid_t  faceId = INVALID_FACE_ID  )
				: half_edge( std::pair<vid_t,vid_t>(f,s), prevHe, nextHe, faceId )
		{
		}

		explicit half_edge( heid_t heid,
							heid_t prevHe = INVALID_EDGE_ID,
							heid_t nextHe = INVALID_EDGE_ID,
							fid_t  faceId = INVALID_FACE_ID  )
					:	id( heid ),
						prev( prevHe),
						next( nextHe),
						incidentFace( faceId )
		{
		}
	};

	//--------------------------------------------------------------------------

	class half_edge_less : public std::binary_function< const half_edge&, const half_edge&, bool >
	{
	public:
		result_type operator() (first_argument_type he1, second_argument_type he2) const
		{
			if ( he1.id.first < he2.id.first )
				return true;

			if ( he1.id.first == he2.id.first )
				return he1.id.second < he2.id.second;

			return false;
		}
	};

	//==========================================================================

	typedef std::set< vertex	, vertex_less	>		vertex_t;
	typedef	std::set< half_edge	, half_edge_less>		half_edge_t;
	typedef std::set< face		, face_less		>		face_t;

	//==========================================================================

}  // namespace ch


#endif /* TYPES_H_ */
