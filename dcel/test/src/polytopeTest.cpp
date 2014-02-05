
#include <vector>
#include <utility>

#include "polytopeTest.h"
#include "polytopeTestUtil.h"


//	---- only to printout
#include <iostream>
using std::cout;
using std::endl;
//	---- only to printout

namespace chtest
{

	// Registers the fixture into the 'registry'
	CPPUNIT_TEST_SUITE_REGISTRATION( polytopeTest );

	//--------------------------------------------------------------------------

	void polytopeTest::setUp()
	{
	}

	void polytopeTest::tearDown()
	{
	}

	//--------------------------------------------------------------------------

	void polytopeTest::testSetLessOperator()
	{
		ch::half_edge he1(2,3);

		bool expValue = true;
		CPPUNIT_ASSERT_EQUAL( expValue, equivalentOp( he1, he1 ) );


		ch::half_edge he2(5,4);

		expValue = false;
		CPPUNIT_ASSERT_EQUAL( expValue, equivalentOp( he1, he2 ) );
		CPPUNIT_ASSERT_EQUAL( expValue, equivalentOp( he2, he1 ) );


		ch::half_edge he3(5,6);

		expValue = false;
		CPPUNIT_ASSERT_EQUAL( expValue, equivalentOp( he3, he2 ) );
		CPPUNIT_ASSERT_EQUAL( expValue, equivalentOp( he2, he3 ) );
	}

	//--------------------------------------------------------------------------

	void polytopeTest::testAddFace()
	{
		ch::polytope polyt;
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( 5 );
		vertIds.push_back( 4 );
		vertIds.push_back( 3 );

		//	Check whether the operation was successful
		bool ret = polyt.addFace( vertIds );
		bool exp = false;

		CPPUNIT_ASSERT_EQUAL( exp, ret );
	}

	//--------------------------------------------------------------------------

	void polytopeTest::testAddFaceCheckFace()
	{
		ch::polytope polyt;
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( 5 );
		vertIds.push_back( 4 );
		vertIds.push_back( 3 );

		bool ret = polyt.addFace( vertIds );
		bool exp = false;

		CPPUNIT_ASSERT_EQUAL( exp, ret );

		//	Check the face IDs in the polytope
		std::unique_ptr< ch::iterator<ch::fid_t> > it = polyt.createFaceIterator();

		for ( it->first(); !it->done(); it->next() )
		{
			ch::fid_t expFaceId = 1;
			ch::fid_t res = it->current();
			
			CPPUNIT_ASSERT_EQUAL( expFaceId, res );
		}
	}

	//--------------------------------------------------------------------------

	void polytopeTest::testAddFaceCheckHalfEdges()
	{
		ch::polytope polyt;
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( 5 );
		vertIds.push_back( 4 );
		vertIds.push_back( 3 );

		bool ret = polyt.addFace( vertIds );
		bool exp = false;

		CPPUNIT_ASSERT_EQUAL( exp, ret );


		//	Create extended vector
		std::vector<ch::vid_t> extVertIds;
		extVertIds.reserve( vertIds.size()+1 );
		std::copy( vertIds.begin(), vertIds.end()		, std::back_inserter( extVertIds ) );
		std::copy( vertIds.begin(), vertIds.begin() + 1	, std::back_inserter( extVertIds ) );

		std::vector<ch::vid_t>::const_iterator vit = extVertIds.begin();


		//	Check the half edge IDs in the face
		std::unique_ptr< ch::iterator<ch::heid_t> > it = polyt.createHalfEdgeIterator( 1 );

		for ( it->first(); !it->done(); it->next(), ++vit )
		{
			ch::heid_t expHalfEdgeId = std::pair<ch::vid_t,ch::vid_t>( *vit, *(vit+1) );

			CPPUNIT_ASSERT_EQUAL( expHalfEdgeId.first , it->current().first  );
			CPPUNIT_ASSERT_EQUAL( expHalfEdgeId.second, it->current().second );
		}
	}

	//--------------------------------------------------------------------------

	void polytopeTest::testAddFaceCheckVertices()
	{
		ch::polytope polyt;
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( 5 );
		vertIds.push_back( 4 );
		vertIds.push_back( 3 );

		bool ret = polyt.addFace( vertIds );
		bool exp = false;

		CPPUNIT_ASSERT_EQUAL( exp, ret );


		//	Check the vertex IDs in the face
		std::unique_ptr< ch::iterator<ch::vid_t> > it = polyt.createVertexIterator( 1 );
		std::vector<ch::vid_t>::const_iterator vit = vertIds.begin();

		for ( it->first(); !it->done(); it->next(), ++vit )
		{
			ch::vid_t expVertexId = *vit;

			CPPUNIT_ASSERT_EQUAL( expVertexId, it->current() );
		}

		CPPUNIT_ASSERT_EQUAL( *vit, *(vertIds.end()) );
	}
	
	//--------------------------------------------------------------------------

	void polytopeTest::testAddFaceCheckFaceExists()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 5, 4, 3 );

		//	Try to add the same face
		addFaceTo( polyt, 5, 4, 3, true );

		//	Try to add the same face beginning with other vertex
		addFaceTo( polyt, 4, 3, 5, true );
	}
	
	//--------------------------------------------------------------------------

	void polytopeTest::testAddFaceCheckHalfEdgesAroundVertex()
	{
		ch::polytope polyt;
		std::vector<ch::vid_t> vertIds;
		vertIds.reserve(4);
		vertIds.push_back( 5 );
		vertIds.push_back( 4 );
		vertIds.push_back( 3 );

		//	Add a face
		bool ret = polyt.addFace( vertIds );
		bool exp = false;

		CPPUNIT_ASSERT_EQUAL( exp, ret );

		std::unique_ptr< ch::iterator<ch::heid_t> > it =
												polyt.createHalfEdgesAroundVertexIterator( *(vertIds.begin()+1) );
		size_t i = 0;
		for ( it->first(); !it->done(); it->next(), ++i )
		{
			CPPUNIT_ASSERT_EQUAL( *(vertIds.begin()+1), it->current().first  );
			CPPUNIT_ASSERT_EQUAL( *(vertIds.begin()+2), it->current().second );
		}

		size_t expRound = 1;
		CPPUNIT_ASSERT_EQUAL( expRound, i );
	}

	//--------------------------------------------------------------------------

	//		0			2				4
	//		<-----------  <-----------
	//		\		   ^/^\			 ^
	//		 \	f1	  //  \\	f3	/
	//		  \		 //	   \\	   /
	//		   \	//		\\	  /
	//			\  //	f2	 \\	 /
	//			 v/v		  \v/
	//			1  ----------->	 3
	//
	void polytopeTest::testMoreFacesCheckHalfEdgesAroundVertex()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 0, 1, 2 );
		addFaceTo( polyt, 2, 1, 3 );
		addFaceTo( polyt, 2, 3, 4 );


		//	Check the faces
		std::vector<ch::fid_t> faceIds;
		faceIds.reserve(4);
		faceIds.push_back( 1 );
		faceIds.push_back( 2 );
		faceIds.push_back( 3 );

		checkFacesIn( polyt, faceIds );


		//	Check the half edges
		std::vector<ch::vid_t> vIds;
		vIds.reserve(4);
		vIds.push_back( 0 );
		vIds.push_back( 1 );
		vIds.push_back( 2 );
		checkHalfEdgesIn( polyt, 1, vIds );

		vIds[0] = 2;
		vIds[1] = 1;
		vIds[2] = 3;
		checkHalfEdgesIn( polyt, 2, vIds );

		vIds[0] = 2;
		vIds[1] = 3;
		vIds[2] = 4;
		checkHalfEdgesIn( polyt, 3, vIds );

		//	Check vertices
		checkVerticesIn( polyt, 1, 0, 1, 2 );
		checkVerticesIn( polyt, 2, 2, 1, 3 );
		checkVerticesIn( polyt, 3, 2, 3, 4 );


		//	Check the half edges around the given vertex
		std::vector< ch::heid_t > expHalfEdges;
		expHalfEdges.reserve(4);
		expHalfEdges.push_back( ch::heid_t(2, 0) );
		expHalfEdges.push_back( ch::heid_t(2, 1) );
		expHalfEdges.push_back( ch::heid_t(2, 3) );

		checkHalfEdgesAroundVertex(	polyt, 2, expHalfEdges );
	}

	//--------------------------------------------------------------------------

	//		0			2				4
	//		<-----------  <-----------
	//		\		   ^/^\			 ^
	//		 \	f2	  //  \\	f3	/
	//		  \		 //	   \\	   /
	//		   \	//		\\	  /
	//			\  //	f1	 \\	 /
	//			 v/v		  \v/
	//			1  ----------->	 3
	//
	void polytopeTest::testMoreFacesCheckHalfEdgesAroundVertex2()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 2, 1, 3 );
		addFaceTo( polyt, 0, 1, 2 );
		addFaceTo( polyt, 2, 3, 4 );


		//	Check the half edges around the given vertex
		std::vector< ch::heid_t > expHalfEdges;
		expHalfEdges.reserve(4);
		expHalfEdges.push_back( ch::heid_t(2, 1) );
		expHalfEdges.push_back( ch::heid_t(2, 0) );
		expHalfEdges.push_back( ch::heid_t(2, 3) );

		checkHalfEdgesAroundVertex(	polyt, 2, expHalfEdges );
	}

	//--------------------------------------------------------------------------

	//		0			2				4
	//		<-----------  <-----------
	//		\		   ^/^\			 ^
	//		 \	f2	  //  \\	f1	/
	//		  \		 //	   \\	   /
	//		   \	//		\\	  /
	//			\  //	f3	 \\	 /
	//			 v/v		  \v/
	//			1  ----------->	 3
	//
	void polytopeTest::testMoreFacesCheckHalfEdgesAroundVertex3()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 4, 2, 3 );
		addFaceTo( polyt, 2, 0, 1 );
		addFaceTo( polyt, 2, 1, 3 );


		//	Check the half edges around the given vertex
		std::vector< ch::heid_t > expHalfEdges;
		expHalfEdges.reserve(4);
		expHalfEdges.push_back( ch::heid_t(2, 3) );
		expHalfEdges.push_back( ch::heid_t(2, 1) );
		expHalfEdges.push_back( ch::heid_t(2, 0) );

		checkHalfEdgesAroundVertex(	polyt, 2, expHalfEdges );
	}

	//--------------------------------------------------------------------------

	//				6			5
	//			   <----------- 
	//			 /^\		  ^/^
	//			/  \\	f5   //  \
	//		   /	\\		//    \
	//		  /		 \\	   //	   \
	//		 /	  f4  \\  //	f6  \
	//		v		   \v/v			 \
	//	  0 ------------> ----------->
	//		<-----------2 <----------- 4
	//		\		   ^/^\			 ^
	//		 \	f3	  //  \\	f1	/
	//		  \		 //	   \\	   /
	//		   \	//		\\	  /
	//			\  //	f2	 \\	 /
	//			 v/v		  \v/
	//			1  ----------->	 3
	//
	void polytopeTest::testMoreFacesCheckHalfEdgesAroundVertex4()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 4, 2, 3 );
		addFaceTo( polyt, 2, 1, 3 );
		addFaceTo( polyt, 2, 0, 1 );
		addFaceTo( polyt, 6, 0, 2 );
		addFaceTo( polyt, 6, 2, 5 );
		addFaceTo( polyt, 5, 2, 4 );

		std::vector< ch::heid_t > expHalfEdges;
		expHalfEdges.reserve(4);
		expHalfEdges.push_back( ch::heid_t(2, 3) );
		expHalfEdges.push_back( ch::heid_t(2, 1) );
		expHalfEdges.push_back( ch::heid_t(2, 0) );
		expHalfEdges.push_back( ch::heid_t(2, 6) );
		expHalfEdges.push_back( ch::heid_t(2, 5) );
		expHalfEdges.push_back( ch::heid_t(2, 4) );

		checkHalfEdgesAroundVertex(	polyt, 2, expHalfEdges );
	}

	//--------------------------------------------------------------------------

	//				/^	5
	//			   / |
	//			  /	 |
	//			 /	 |
	//			/	 |
	//		 4 v	 |
	//		   ------>	3
	//
	void polytopeTest::testAddRemoveFace()
	{
		ch::polytope polyt;

		addFaceTo( polyt, 5, 4, 3 );
		removeFaceFrom( polyt, 1 );

		//	Checking the nonexisting faces
		std::vector<ch::fid_t> faceIds;
		faceIds.push_back( 1 );

		checkNonExistingFacesIn( polyt, faceIds );

		removeFaceFrom( polyt, 1, false );

		//	We are not able to check directly the removed vertices and edges. If
		//	the original face is added again and some vertices or egdes would
		//	have remained then during the addition the asserts in the code will
		//	interrupt the test execution.
		addFaceTo( polyt, 5, 4, 3 );

		removeFaceFrom( polyt, 2 );
	}

	//--------------------------------------------------------------------------

	//				5 <------	6
	//				/^|		^
	//			   / ||	f2 /
	//			  /	 ||	  /
	//			 /	 ||	 /
	//			/ f1 ||	/
	//		 4 v	 |v/
	//		   ------>	3
	//
	void polytopeTest::testAddRemoveFaces()
	{
		ch::polytope polyt;

		addFaceTo( polyt, 5, 4, 3 );	//	face 1
		addFaceTo( polyt, 5, 3, 6 );	//	face 2
		removeFaceFrom( polyt, 1 );

		//	Checking the nonexisting faces
		std::vector<ch::fid_t> faceIds;
		faceIds.push_back( 1 );

		checkNonExistingFacesIn( polyt, faceIds );

		removeFaceFrom( polyt, 1, false );

		addFaceTo( polyt, 5, 4, 3 );	//	face 3
		removeFaceFrom( polyt, 3 );
	}

	//--------------------------------------------------------------------------

	//				 0 /^
	//				  /	 \
	//				 /	  \
	//				/  f1  \
	//			   /		\
	//			  v			 \
	//			1 ----------->  2
	//			  <-----------
	//		    /^\			 ^/^
	//		   /  \\   f3	//  \
	//		  /	   \\	   //	 \
	//		 /		\\	  //	  \
	//		/	f2	 \\	 //	  f4   \
	//	   v		  \v/v		    \
	//	 3 ----------->4 ----------->	5
	//
	void polytopeTest::testAddRemoveMoreFaces()
	{
		ch::polytope polyt;

		addFaceTo( polyt, 0, 1, 2 );	//	face 1
		addFaceTo( polyt, 1, 3, 4 );	//	face 2
		addFaceTo( polyt, 1, 4, 2 );	//	face 3
		addFaceTo( polyt, 2, 4, 5 );	//	face 4
		removeFaceFrom( polyt, 3 );

		//	Checking the nonexisting faces
		std::vector<ch::fid_t> faceIds;
		faceIds.push_back( 3 );

		checkNonExistingFacesIn( polyt, faceIds );

		removeFaceFrom( polyt, 3, false );

		addFaceTo( polyt, 1, 4, 2 );	//	face 5
		removeFaceFrom( polyt, 5 );
	}

	//--------------------------------------------------------------------------

	//		0			2				4
	//		<-----------  <-----------
	//		\		   ^/^\			 ^
	//		 \	f1	  //  \\	f3	/
	//		  \		 //	   \\	   /
	//		   \	//		\\	  /
	//			\  //	f2	 \\	 /
	//			 v/v		  \v/
	//			1  ----------->	 3
	//
	void polytopeTest::testMergeFacesNonAdjacent()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 2, 0, 1 );
		addFaceTo( polyt, 2, 1, 3 );
		addFaceTo( polyt, 2, 3, 4 );

		mergeFaces( polyt, 1, 3, false );
	}

	//--------------------------------------------------------------------------

	//		0			2				4
	//		<-----------  <-----------
	//		\		   ^/^\			 ^
	//		 \	f1	  //  \\	f3	/
	//		  \		 //	   \\	   /
	//		   \	//		\\	  /
	//			\  //	f2	 \\	 /
	//			 v/v		  \v/
	//			1  ----------->	 3
	//
	void polytopeTest::testMergeFacesAdjacent()
	{
		ch::polytope polyt;
		addFaceTo( polyt, 1, 2, 0 );
		addFaceTo( polyt, 2, 1, 3 );
		addFaceTo( polyt, 2, 3, 4 );

		mergeFaces( polyt, 1, 2 );
	}

	//--------------------------------------------------------------------------

}




