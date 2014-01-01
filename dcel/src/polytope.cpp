

#include <algorithm>
#include <cassert>
#include <iterator>

#include "polytope.h"
#include "assert_messages.h"

using std::back_inserter;
using std::copy;
using std::pair;
using std::unique_ptr;
using std::vector;


//	---- only to printout
#include <iostream>
using std::cout;
using std::endl;
//	---- only to printout


namespace ch
{
	polytope::polytope() : faceIdCounter(0), accVertex(0), accHalfEdge(0,0), accFace(0) {}

	//--------------------------------------------------------------------------

	bool polytope::addFace( const vector<vid_t>& vertexIds )
	{
		if ( faceExists( vertexIds ) )
			return true;

		assert( vertexIds.size() > 2 );


		vector<vid_t> extVertIds;		//	extended vertex ids
		extVertIds.reserve( vertexIds.size()+3 );
		
		vector<vid_t>::const_iterator end  = vertexIds.end();
		vector<vid_t>::const_iterator last = end-1;

		copy( last,				end,				back_inserter(extVertIds) );
		copy( vertexIds.begin(),vertexIds.end(),	back_inserter(extVertIds) );
		copy( vertexIds.begin(),vertexIds.begin()+2,back_inserter(extVertIds) );

		end = extVertIds.end()-2;
		vector<vid_t>::const_iterator begin = extVertIds.begin()+1;

		fid_t faceId = getNextFaceId();
		faces.insert( face( faceId, pair<vid_t,vid_t>(*begin, *(begin+1)) ) );

		for ( vector<vid_t>::const_iterator it = begin;  it != end;  ++it )
		{
			addVertexAndIncidentEdge(	*it,
										pair<vid_t,vid_t>(*it, *(it+1)),		//	incidentEdge
										pair<vid_t,vid_t>(*(it-1), *it),		//	prevHe
										pair<vid_t,vid_t>(*(it+1), *(it+2)),	//	nextHe
										faceId );
		}

		return false;
	}

	//--------------------------------------------------------------------------

	bool polytope::removeFace( fid_t fid )
	{
		if ( !faceExists( fid ) )
			return false;

		accFace.id = fid;
		face_t::iterator fit = faces.find( accFace );

		assert( fit != faces.end() );

		heid_t firstHalfEdge	= fit->outerComponent;
		heid_t currentHalfEdge	= firstHalfEdge;
		bool firstHeLeft		= false;

		for ( ; currentHalfEdge != firstHalfEdge  ||  !firstHeLeft; )
		{
			vid_t vid = currentHalfEdge.first;

			unique_ptr< iterator<heid_t> > heavit = createHalfEdgesAroundVertexIterator( vid );

			heavit->first(); heavit->next();

			if ( heavit->done() )
			{
				accVertex.id = vid;
				vertices.erase( accVertex );
			}
			else
			{
				accVertex.id = vid;

				//	Change the incidentEdge member of the vertex
				vertex_t::iterator vchit = vertices.find( accVertex );
				assert( vchit != vertices.end()  &&  CH_ASSERTSTR_INVALID_VERTEXID );

				accVertex.incidentEdge = heavit->current();

				vertices.erase( vchit );
				vertices.insert( vchit, accVertex );
			}

			accHalfEdge.id = currentHalfEdge;
			half_edge_t::iterator currit = half_edges.find( accHalfEdge );
			assert( currit != half_edges.end()  &&  CH_ASSERTSTR_INVALID_HALFEDGEID );

			currentHalfEdge = currit->next;

			half_edges.erase( currit );

			firstHeLeft	= true;
		}

		//accFace.id = fid;
		faces.erase( accFace );
		assert( faces.find( accFace ) == faces.end() );

		return true;
	}

	//--------------------------------------------------------------------------

	bool polytope::mergeFaces( fid_t fid1, fid_t fid2 )
	{
		if ( fid1 == fid2 )			return false;
		if ( !faceExists( fid1 ) )	return false;
		if ( !faceExists( fid2 ) )	return false;

		heid_t firstAdjacentEdge;
		if ( !areFacesAdjacent( fid1, fid2, firstAdjacentEdge ) )	return false;

		cout << "\nafter areFacesAdjacent firstAdjacentEdge: "<< firstAdjacentEdge.first << "," <<
																	firstAdjacentEdge.second << "\n" << endl;

		//	Save the previous edges
		getHalfEdge( firstAdjacentEdge, accHalfEdge );
		heid_t backwPrevHeId = accHalfEdge.prev;

		bool twinExists = twinHalfEdgeExists( firstAdjacentEdge, accHalfEdge );
		assert( twinExists  &&  CH_ASSERTSTR_INVALID_TWINHALFEDGEID );
		heid_t backwNextTwinHeId = accHalfEdge.next;

		cout << "\nafter saving previous edges\n" << endl;

		//	The forward iteration
		for ( heid_t currentHeId = firstAdjacentEdge
					,twinHeId	 = getTwinHalfEdgeId(firstAdjacentEdge); ; )
		{
			//	Save the next edges
			getHalfEdge( currentHeId, accHalfEdge );
			heid_t nextHeId = accHalfEdge.next;

			getHalfEdge( twinHeId, accHalfEdge );
			heid_t prevTwinHeId = accHalfEdge.prev;

			removeHalfEdge( currentHeId	);
			removeHalfEdge( twinHeId	);

			//	currentHeId		nextHeId
			//	------------> -------------->
			//	<------------ <--------------
			//		twinHeId	prevTwinHeId
			//
			if ( nextHeId == getTwinHalfEdgeId(prevTwinHeId) )
			{
				currentHeId	= nextHeId;
				twinHeId	= prevTwinHeId;
			}
			//					 ^
			//					/
			//	currentHeId	   /	nextHeId
			//	------------> /
			//	<------------ ^
			//		twinHeId   \	prevTwinHeId
			//					\
			//					 \.
			else
			{
				replaceHalfEdgeNext( prevTwinHeId, nextHeId		);
				replaceHalfEdgePrev( nextHeId	 , prevTwinHeId	);
				cout << "\nend of forward iteration prevTwinHeId: "<< prevTwinHeId.first << ","
																	<< prevTwinHeId.second << "\n" << endl;
				
				getHalfEdge( nextHeId, accHalfEdge );
				cout << "nextHeId: " << nextHeId.first<< ", " << nextHeId.second
					<< "prev: " << accHalfEdge.prev.first << ", " << accHalfEdge.prev.second
					<< endl;
				
//				getHalfEdge( 
				break;
			}
		}

		cout << "\nafter forward iteration\n" << endl;

		heid_t firstIn2ndFaceIt;

		//	The backward iteration
		for ( heid_t currentHeId = backwPrevHeId
					,twinHeId	 = backwNextTwinHeId; ; )
		{
			getHalfEdge( currentHeId, accHalfEdge );
			heid_t prevHeId = accHalfEdge.prev;

			getHalfEdge( twinHeId, accHalfEdge );
			heid_t nextTwinHeId = accHalfEdge.next;

			//		   /
			//		  /	prevHeId
			//		 /
			//		v		currentHeId
			//		---------->
			//		<----------
			//		\		twinHeId
			//		 \
			//		  \	nextTwinHeId
			//		   v
			if ( currentHeId == getTwinHalfEdgeId(twinHeId) )
			{
				removeHalfEdge( currentHeId	);		currentHeId	= prevHeId;
				removeHalfEdge( twinHeId	);		twinHeId	= nextTwinHeId;
			}
			else
			{
				replaceHalfEdgeNext( currentHeId, twinHeId		);
				replaceHalfEdgePrev( twinHeId	, currentHeId	);
				firstIn2ndFaceIt = twinHeId;
				break;
			}
		}

		cout << "\nafter backward iteration\n" << endl;

		//	Write over the face ids in the half edges which belonged to the 2nd face.
		for ( heid_t currentHeId = firstIn2ndFaceIt; ; )
		{
			cout << "\n currHeId: " << currentHeId.first << ", " << currentHeId.second << endl;
			getHalfEdge( currentHeId, accHalfEdge );
			if ( accHalfEdge.incidentFace == fid2 )
			{
				accHalfEdge.incidentFace = fid1;
				currentHeId = accHalfEdge.next;
			}
			else
			{
				break;
			}
		}

		cout << "\nafter face id overwrite\n" << endl;

		return true;
	}

	bool polytope::areFacesAdjacent( fid_t fid1, fid_t fid2, heid_t& adjHeId ) const
	{
		getFace( fid1, accFace );

		heid_t currentHeId = accFace.outerComponent;
		const heid_t firstHeId = currentHeId;
		bool firstHeLeft = false;

		for ( ; currentHeId != firstHeId || !firstHeLeft; )
		{
			if ( twinHalfEdgeExists( currentHeId, accHalfEdge ) )
			{
				if ( accHalfEdge.incidentFace == fid2 )
				{
					adjHeId = currentHeId;
					return true;
				}
			}

			getHalfEdge( currentHeId, accHalfEdge );
			currentHeId = accHalfEdge.next;
			firstHeLeft = true;
		}

		return false;
	}

	//==========================================================================
	//	Private member functions
	//==========================================================================

	size_t polytope::vertexNumber() const
	{
		return vertices.size();
	}

	size_t polytope::halfEdgeNumber() const
	{
		return half_edges.size();
	}

	size_t polytope::faceNumber() const
	{
		return faces.size();
	}


	bool polytope::vertexExists( const vid_t vid ) const
	{
		accVertex.id = vid;
		return vertices.find( accVertex ) != vertices.end();
	}
	//--------------------------------------------------------------------------

	bool polytope::halfEdgeExists( const vid_t first, const vid_t second ) const
	{
		accHalfEdge.id.first	= first ;
		accHalfEdge.id.second	= second;
		return half_edges.find( accHalfEdge ) != half_edges.end();
	}
	
	bool polytope::halfEdgeExists( heid_t heid ) const
	{
		return half_edges.find( ( accHalfEdge.id = heid, accHalfEdge ) ) != half_edges.end();
	}

	bool polytope::halfEdgeExists( heid_t heid, half_edge& he ) const
	{
		half_edge_t::const_iterator heit = half_edges.find( ( accHalfEdge.id = heid, accHalfEdge ) );
		bool ret = heit != half_edges.end();

		if ( ret )
			he = *heit;

		return ret;
	}

	void polytope::getHalfEdge( heid_t heid, half_edge& he ) const
	{
		half_edge_t::const_iterator heit = half_edges.find( ( accHalfEdge.id = heid, accHalfEdge ) );

		assert( heit != half_edges.end()  &&  CH_ASSERTSTR_INVALID_HALFEDGEID );

		he = *heit;
	}

	void polytope::removeHalfEdge( heid_t heid )
	{
		half_edge_t::size_type number = half_edges.erase( (accHalfEdge.id = heid, accHalfEdge) );
		assert( number == 1 );
	}

	void polytope::replaceHalfEdgeNext( heid_t toBeReplaceHeId, heid_t replaceWithHeId )
	{
		replaceHalfEdge( toBeReplaceHeId, replaceWithHeId, &polytope::halfEdgeModifierNext );
	}

	void polytope::replaceHalfEdgePrev( heid_t toBeReplaceHeId, heid_t replaceWithHeId )
	{
		replaceHalfEdge( toBeReplaceHeId, replaceWithHeId, &polytope::halfEdgeModifierPrev );
	}

	void polytope::replaceHalfEdge(	heid_t toBeReplaceHeId, heid_t replaceWithHeId,
									void (polytope::*modifier)(half_edge&, heid_t) )
	{
		half_edge_t::const_iterator heit = half_edges.find( ( accHalfEdge.id = toBeReplaceHeId, accHalfEdge ) );

		assert( heit != half_edges.end()  &&  CH_ASSERTSTR_INVALID_HALFEDGEID );

		accHalfEdge = *heit;
		(this->*modifier)( accHalfEdge, replaceWithHeId );
//		accHalfEdge.next = replaceWithHeId;

		half_edges.erase( heit );
		std::pair<half_edge_t::iterator, bool> pit = half_edges.insert( /*heit,*/ accHalfEdge );
		assert( pit.second == true  &&  "Insertion failed!" );
	}

	void polytope::halfEdgeModifierNext( half_edge& he, heid_t nextVal )
	{
		he.next = nextVal;
	}

	void polytope::halfEdgeModifierPrev( half_edge& he, heid_t prevVal )
	{
		he.prev = prevVal;
	}
	//--------------------------------------------------------------------------

	bool polytope::twinHalfEdgeExists( const heid_t heid ) const
	{
		accHalfEdge.id.first	= heid.second;
		accHalfEdge.id.second	= heid.first;
		return half_edges.find( accHalfEdge ) != half_edges.end();
	}

	bool polytope::twinHalfEdgeExists( const heid_t heid, half_edge& he ) const
	{
		accHalfEdge.id.first	= heid.second ;
		accHalfEdge.id.second	= heid.first;
		half_edge_t::const_iterator twinHeit = half_edges.find( accHalfEdge );
		bool ret = twinHeit != half_edges.end();

		if ( ret )
			he = *twinHeit;

		return ret;
	}

	heid_t polytope::getTwinHalfEdgeId( const heid_t heid ) const
	{
		return heid_t( heid.second, heid.first );
	}
	//--------------------------------------------------------------------------

	bool polytope::faceExists( const vector<vid_t>& vertIds ) const
	{
		vector<vid_t> extVertexIds;		//	extended vertex ids
	
		extVertexIds.reserve( vertIds.size()+1 );
	
		copy( vertIds.begin(), vertIds.end()    , back_inserter(extVertexIds) );
	
		copy( vertIds.begin(), vertIds.begin()+1, back_inserter(extVertexIds) );

	
		vector<vid_t>::const_iterator end = extVertexIds.end()-1;

		for( vector<vid_t>::iterator it = extVertexIds.begin();  it != end;  ++it )
		{
			if ( !vertexExists( *it ) )
				return false;

			if ( !halfEdgeExists( *it, *(it+1) ) )
				return false;
		}
		
		return true;
	}
	
	bool polytope::faceExists( const fid_t faceId ) const
	{
		accFace.id = faceId;
		return faces.find( accFace ) != faces.end();
	}

	bool polytope::faceExists( const fid_t faceId, face& face ) const
	{
		face_t::const_iterator fit = faces.find( ( accFace.id = faceId, accFace ) );
		bool exists = fit != faces.end();

		assert( fit != faces.end()  &&  CH_ASSERTSTR_INVALID_FACEID );

		if ( exists )
			face = *fit;

		return exists;
	}

	void polytope::getFace( const fid_t faceId, face& face ) const
	{
		face_t::const_iterator fit = faces.find( ( accFace.id = faceId, accFace ) );

		assert( fit != faces.end()  &&  CH_ASSERTSTR_INVALID_FACEID );

		face = *fit;
	}
	//--------------------------------------------------------------------------

	fid_t polytope::getNextFaceId()
	{
		return ++faceIdCounter;
	}

	void polytope::addVertexAndIncidentEdge(vid_t vertId, heid_t&& incidentEdgeId,
											heid_t&& prevHeId, heid_t&& nextHeId,
											fid_t faceId )
	{
		if ( !vertexExists(vertId) ) {
			pair<vertex_t::iterator, bool> v_res = vertices.insert( vertex(vertId, incidentEdgeId) );

			assert( v_res.second );
		}

		assert( !halfEdgeExists(incidentEdgeId) );

		pair<half_edge_t::iterator, bool> he_res = half_edges.insert( half_edge(incidentEdgeId,
																				prevHeId,
																				nextHeId,
																				faceId ) );
		assert( he_res.second );

		assert( he_res.first->id.first  == incidentEdgeId.first  );
		assert( he_res.first->id.second == incidentEdgeId.second );

		assert( he_res.first->prev.first  == prevHeId.first  );
		assert( he_res.first->prev.second == prevHeId.second );

		assert( he_res.first->next.first  == nextHeId.first  );
		assert( he_res.first->next.second == nextHeId.second );

		assert( he_res.first->incidentFace == faceId );
	}

}




