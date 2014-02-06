

#ifndef POLYTOPETEST_H_
#define POLYTOPETEST_H_

#include <cppunit/extensions/HelperMacros.h>


namespace chtest
{

	class polytopeTest: public CppUnit::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE( polytopeTest );
		CPPUNIT_TEST( testSetLessOperator				);
		CPPUNIT_TEST( testAddFace						);
		CPPUNIT_TEST( testAddFaceCheckFace				);
		CPPUNIT_TEST( testAddFaceCheckHalfEdges			);
		CPPUNIT_TEST( testAddFaceCheckVertices			);
		CPPUNIT_TEST( testAddFaceCheckFaceExists		);
		CPPUNIT_TEST( testAddFaceCheckHalfEdgesAroundVertex			);
		CPPUNIT_TEST( testMoreFacesCheckHalfEdgesAroundVertex		);
		CPPUNIT_TEST( testMoreFacesCheckHalfEdgesAroundVertex2		);
		CPPUNIT_TEST( testMoreFacesCheckHalfEdgesAroundVertex3		);
		CPPUNIT_TEST( testMoreFacesCheckHalfEdgesAroundVertex4		);

		CPPUNIT_TEST( testAddRemoveFace								);
		CPPUNIT_TEST( testAddRemoveFaces							);
		CPPUNIT_TEST( testAddRemoveMoreFaces						);

		CPPUNIT_TEST( testMergeFacesNonAdjacent						);
		CPPUNIT_TEST( testMergeFacesAdjacent						);
		CPPUNIT_TEST( testMergeFacesAdjacentBeginningWithPrecedingEdge			);
		CPPUNIT_TEST( testMergeFacesAdjacentBeginningWithFirstCommonEdge		);
		CPPUNIT_TEST( testMergeFacesAdjacentBeginningWithMidCommonEdge			);
		CPPUNIT_TEST( testMergeFacesAdjacentBeginningWithLastCommonEdge			);
		CPPUNIT_TEST( testMergeFacesAdjacentBeginningWithLastCommonFollowedEdge	);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testSetLessOperator();

		void testAddFace();
		void testAddFaceCheckFace();
		void testAddFaceCheckHalfEdges();
		void testAddFaceCheckVertices();
		void testAddFaceCheckFaceExists();

		void testAddFaceCheckHalfEdgesAroundVertex();
		void testMoreFacesCheckHalfEdgesAroundVertex();
		void testMoreFacesCheckHalfEdgesAroundVertex2();
		void testMoreFacesCheckHalfEdgesAroundVertex3();
		void testMoreFacesCheckHalfEdgesAroundVertex4();

		void testAddRemoveFace();
		void testAddRemoveFaces();
		void testAddRemoveMoreFaces();

		void testMergeFacesNonAdjacent();
		void testMergeFacesAdjacent();
		void testMergeFacesAdjacentBeginningWithPrecedingEdge();
		void testMergeFacesAdjacentBeginningWithFirstCommonEdge();
		void testMergeFacesAdjacentBeginningWithMidCommonEdge();
		void testMergeFacesAdjacentBeginningWithLastCommonEdge();
		void testMergeFacesAdjacentBeginningWithLastCommonFollowedEdge();
	};

}

#endif /* POLYTOPETEST_H_ */
