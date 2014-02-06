
#include "polytopeTestUtil.h"
#include <cppunit/extensions/HelperMacros.h>

namespace chtest
{

	//--------------------------------------------------------------------------

	bool equivalentOp( ch::half_edge he1, ch::half_edge he2 )
	{
		ch::half_edge_less lessOperator;

		return ! lessOperator( he1, he2 )  &&  ! lessOperator( he2, he1 );
	}

	//--------------------------------------------------------------------------

	void addFaceTo( ch::polytope& polyt, ch::vid_t v1, ch::vid_t v2, ch::vid_t v3, bool expVal )
	{
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( v1 );
		vertIds.push_back( v2 );
		vertIds.push_back( v3 );

		//	Add a face
		bool ret = polyt.addFace( vertIds );

		CPPUNIT_ASSERT_EQUAL( expVal, ret );
	}

	//--------------------------------------------------------------------------

	void removeFaceFrom( ch::polytope& polyt, ch::fid_t fid, bool expVal )
	{
		bool ret = polyt.removeFace( fid );

		CPPUNIT_ASSERT_EQUAL( expVal, ret );
	}

	//--------------------------------------------------------------------------

	void checkFacesIn( const ch::polytope& polyt, const std::vector<ch::fid_t>& faceIds )
	{
		//	Check the face IDs in the polytope
		std::unique_ptr< ch::iterator<ch::fid_t> > it = polyt.createFaceIterator();

		size_t i = 0;
		for ( it->first(); !it->done(); it->next(), ++i )
		{
			CPPUNIT_ASSERT_EQUAL( faceIds[i], it->current() );
		}

		CPPUNIT_ASSERT_EQUAL( faceIds.size(), i );
	}

	//--------------------------------------------------------------------------

	void checkHalfEdgesIn(	const ch::polytope& polyt, ch::fid_t fid,
											const std::vector<ch::heid_t>& heIds )
	{
		//	Check the half edge IDs in the face
		std::unique_ptr< ch::iterator<ch::heid_t> > it = polyt.createHalfEdgeIterator( fid );

		std::vector<ch::heid_t>::const_iterator heit = heIds.begin();

		size_t i = 0;
		for ( it->first(); !it->done(); it->next(), ++heit, ++i )
		{
			CPPUNIT_ASSERT_EQUAL( heit->first , it->current().first  );
			CPPUNIT_ASSERT_EQUAL( heit->second, it->current().second );
		}

		CPPUNIT_ASSERT_EQUAL( heIds.size(), i );
	}

	//--------------------------------------------------------------------------

	void checkHalfEdgesIn(	const ch::polytope& polyt, ch::fid_t fid,
											const std::vector<ch::vid_t >&  vIds )
	{
		std::vector<ch::heid_t > heIds;
		heIds.reserve(8);

		size_t i = 0;
		for ( ; i < vIds.size()-1; ++i )
		{
			heIds.push_back( ch::heid_t(vIds[i],vIds[i+1]) );
		}

		heIds.push_back( ch::heid_t(vIds[i],vIds[0]) );

		CPPUNIT_ASSERT_EQUAL( vIds.size(), heIds.size() );
		
		checkHalfEdgesIn( polyt, fid, heIds );
	}

	//--------------------------------------------------------------------------

	void checkVerticesIn( const ch::polytope& polyt, ch::fid_t fid,
										ch::vid_t v1, ch::vid_t v2, ch::vid_t v3 )
	{
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( v1 );
		vertIds.push_back( v2 );
		vertIds.push_back( v3 );

		std::vector<ch::vid_t>::const_iterator vit = vertIds.begin();

		//	Check the vertex IDs in the face
		std::unique_ptr< ch::iterator<ch::vid_t> > it = polyt.createVertexIterator( fid );

		for ( it->first(); !it->done(); it->next(), ++vit )
		{
			ch::vid_t expVertexId = *vit;

			CPPUNIT_ASSERT_EQUAL( expVertexId, it->current() );
		}

		CPPUNIT_ASSERT_EQUAL( *vit, *(vertIds.end()) );
	}

	//--------------------------------------------------------------------------

	void checkHalfEdgesAroundVertex(	const ch::polytope& polyt, ch::vid_t vid,
													const std::vector<ch::heid_t>& expHalfEdges )
	{
		//	Check the half edges around the given vertex
		std::unique_ptr< ch::iterator<ch::heid_t> > it = polyt.createHalfEdgesAroundVertexIterator( vid );

		std::vector< ch::heid_t >::const_iterator heit = expHalfEdges.begin();

		size_t i = 0;
		for ( it->first(); !it->done(); it->next(), ++i, ++heit )
		{
			CPPUNIT_ASSERT_EQUAL( heit->first , it->current().first  );
			CPPUNIT_ASSERT_EQUAL( heit->second, it->current().second );
		}

		CPPUNIT_ASSERT_EQUAL( expHalfEdges.size(), i );
	}

	//--------------------------------------------------------------------------

	void checkNonExistingFacesIn( const ch::polytope& polyt, const std::vector<ch::fid_t>& faceIds )
	{
		//	Check the face IDs in the polytope
		std::unique_ptr< ch::iterator<ch::fid_t> > it = polyt.createFaceIterator();

		for ( std::vector<ch::fid_t>::const_iterator cfit = faceIds.begin(); cfit != faceIds.end(); ++cfit )
		{
			size_t i = 0;
			for ( it->first(); !it->done(); it->next(), ++i )
			{
				bool equality = it->current() == *cfit;
				CPPUNIT_ASSERT_EQUAL( false, equality );
			}
		}
	}

	//--------------------------------------------------------------------------

	void mergeFaces( ch::polytope& polyt, ch::fid_t fid1, ch::fid_t fid2, bool expVal )
	{
		bool ret = polyt.mergeFaces( fid1, fid2 );
		CPPUNIT_ASSERT_EQUAL( expVal, ret );
	}

	//--------------------------------------------------------------------------

	void checkMergedFace( const ch::polytope& polyt, const std::vector<ch::vid_t>& vertIds )
	{
		//	Checking the nonexisting face
		std::vector<ch::fid_t> faceIds = { 2 };
		checkNonExistingFacesIn( polyt, faceIds );

		//	Go around the face and check whether all the vertices are correct
		std::unique_ptr< ch::iterator<ch::vid_t> > it = polyt.createVertexIterator( 1 );
		std::vector<ch::vid_t>::const_iterator vit = vertIds.begin();

		for ( it->first(); !it->done(); it->next(), ++vit )
		{
			ch::vid_t expVertexId = *vit;
			CPPUNIT_ASSERT_EQUAL( expVertexId, it->current() );
		}
		CPPUNIT_ASSERT_EQUAL( *vit, *(vertIds.end()) );

		//	Create extended vector
		std::vector<ch::vid_t> extVertIds;
		extVertIds.reserve( vertIds.size()+1 );
		std::copy( vertIds.begin(), vertIds.end()		, std::back_inserter( extVertIds ) );
		std::copy( vertIds.begin(), vertIds.begin() + 1	, std::back_inserter( extVertIds ) );

		vit = extVertIds.begin();

		//	Check the half edge IDs in the face
		std::unique_ptr< ch::iterator<ch::heid_t> > heit = polyt.createHalfEdgeIterator( 1 );

		for ( heit->first(); !heit->done(); heit->next(), ++vit )
		{
			ch::heid_t expHalfEdgeId = std::pair<ch::vid_t,ch::vid_t>( *vit, *(vit+1) );

			CPPUNIT_ASSERT_EQUAL( expHalfEdgeId.first , heit->current().first  );
			CPPUNIT_ASSERT_EQUAL( expHalfEdgeId.second, heit->current().second );
		}
	}

	//--------------------------------------------------------------------------

}
