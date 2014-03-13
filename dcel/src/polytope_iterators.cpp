
#include <cassert>

#include "polytope.h"
#include "assert_messages.h"

using std::back_inserter;
using std::copy;
using std::pair;
using std::unique_ptr;
using std::vector;


namespace ch
{

	//==========================================================================
	//	Iterator creation related part
	//==========================================================================

	unique_ptr< iterator<fid_t > > polytope::createFaceIterator() const
	{
		return unique_ptr< iterator<fid_t> >( new face_iterator(faces) );
	}
	
	unique_ptr< iterator<heid_t> > polytope::createHalfEdgeIterator	( fid_t faceId ) const
	{
		assert( faceExists( faceId ) && CH_ASSERTSTR_INVALID_FACEID );

		face_t::const_iterator it = faces.find( face( faceId ) );
		heid_t heid = it->outerComponent;

		return unique_ptr< iterator<heid_t> >( new half_edge_iterator	( heid, half_edges ) );
	}

	unique_ptr< iterator<vid_t > > polytope::createVertexIterator	( fid_t faceId ) const
	{
		return unique_ptr< iterator<vid_t> >( new vertex_iterator( polytope::createHalfEdgeIterator(faceId) ) );
	}

	unique_ptr< iterator<heid_t> > polytope::createHalfEdgesAroundVertexIterator(vid_t vertexId) const
	{
		assert( vertexExists( vertexId ) && CH_ASSERTSTR_INVALID_VERTEXID );

		vertex_t::const_iterator vit = vertices.find( vertex( vertexId ) );

		return unique_ptr< iterator<heid_t> >( new half_edges_around_vertex_iterator( vit->incidentEdge, half_edges ) );
	}

	//==========================================================================
	//	Face iterator related part
	//==========================================================================

	polytope::face_iterator::face_iterator( const face_t& faceColl ) : faceCollection( faceColl )
	{
	}

	void polytope::face_iterator::first()
	{
		faceIt = faceCollection.begin();
	}

	void polytope::face_iterator::next()
	{
		if ( !done() )
			++faceIt;
	}

	bool polytope::face_iterator::done()
	{
		return faceCollection.end() == faceIt;
	}

	const fid_t& polytope::face_iterator::current() const
	{
		return faceIt->id;
	}

	//==========================================================================
	//	Half edge iterator related part
	//==========================================================================

	polytope::half_edge_iterator::half_edge_iterator( heid_t first, const half_edge_t& halfEdgeColl )
										: firstHalfEdge( first ), halfEdgeCollection( halfEdgeColl )
	{
	}

	void polytope::half_edge_iterator::first()
	{
		currentHalfEdge = firstHalfEdge;
		firstHeLeft = 0;
	}

	void polytope::half_edge_iterator::next()
	{
		if ( !done() )
		{
			half_edge_t::const_iterator heIt = halfEdgeCollection.find( half_edge(currentHalfEdge) );

			assert( heIt != halfEdgeCollection.end() );

			currentHalfEdge = heIt->next;
			firstHeLeft = 1;
		}
	}

	bool polytope::half_edge_iterator::done()
	{
		return currentHalfEdge == firstHalfEdge  &&  firstHeLeft;
	}

	const heid_t& polytope::half_edge_iterator::current() const
	{
		return currentHalfEdge;
	}

	//==========================================================================
	//	Vertex id iterator related part
	//==========================================================================

	polytope::vertex_iterator::vertex_iterator( std::unique_ptr< iterator<heid_t> >&& halfEdgeIterator )
																	: heit( std::move(halfEdgeIterator) )
	{
	}

	void polytope::vertex_iterator::first()
	{
		heit->first();
	}

	void polytope::vertex_iterator::next()
	{
		heit->next();
	}

	bool polytope::vertex_iterator::done()
	{
		return heit->done();
	}

	const vid_t& polytope::vertex_iterator::current() const
	{
		return heit->current().first;
	}

	//==========================================================================
	//	Half Edge IDs around Vertex iterator related part
	//==========================================================================

	polytope::half_edges_around_vertex_iterator::half_edges_around_vertex_iterator(  heid_t first
																					,const half_edge_t& halfEdgeColl )
																			:	 firstHalfEdge( first )
																				,halfEdgeCollection( halfEdgeColl )
	{
	}

	void polytope::half_edges_around_vertex_iterator::first()
	{
		currentHalfEdge = firstHalfEdge;
		firstHeLeft		= 0;
		leftSideEnd		= 0;
		rightSideEnd	= 0;
	}

	void polytope::half_edges_around_vertex_iterator::next()
	{
		if ( !done() )
		{
			if ( !leftSideEnd )
			{
				if ( twinHalfEdgeExists( currentHalfEdge ) )
				{
					//	Get the twin he
					half_edge_t::const_iterator twinIt =
								halfEdgeCollection.find( half_edge(currentHalfEdge.second, currentHalfEdge.first ) );

					assert( twinIt != halfEdgeCollection.end() );

					//	Get the next he
					currentHalfEdge = twinIt->next;
					firstHeLeft = 1;
				}
				else
				{
					currentHalfEdge = firstHalfEdge;
					leftSideEnd = 1;
				}
			}

			if ( leftSideEnd  &&  !rightSideEnd )
			{
				//	Get the prev he
				half_edge_t::const_iterator heIt = halfEdgeCollection.find( half_edge(currentHalfEdge) );

				assert( heIt != halfEdgeCollection.end() );

				currentHalfEdge = heIt->prev;

				//	Get the twin he
				if ( twinHalfEdgeExists( currentHalfEdge ) )
				{
					half_edge_t::const_iterator twinIt =
								halfEdgeCollection.find( half_edge(currentHalfEdge.second, currentHalfEdge.first ) );

					assert( twinIt != halfEdgeCollection.end() );

					currentHalfEdge = twinIt->id;
					firstHeLeft = 1;
				}
				else
				{
					rightSideEnd = 1;
				}
			}
		}
	}

	bool polytope::half_edges_around_vertex_iterator::done()
	{
		return ( currentHalfEdge == firstHalfEdge  &&  firstHeLeft )
			||  ( leftSideEnd  &&  rightSideEnd );
	}
	
	const heid_t& polytope::half_edges_around_vertex_iterator::current() const
	{
		return currentHalfEdge;
	}

	//	WARNING: duplicated code. See polytope::twinHalfEdgeExists.
	bool polytope::half_edges_around_vertex_iterator::twinHalfEdgeExists( const heid_t heid ) const
	{
		half_edge he( heid.second, heid.first );
		return halfEdgeCollection.find( he ) != halfEdgeCollection.end();
	}

}
