

#include <vector>
#include "vertexchooserTest.h"

#include "collection_impl.h"
#include "dataholder_impl.h"
#include "thvch_impl.h"

//	---- only to printout
#include <iostream>
using std::cout;
using std::endl;
//	---- only to printout

namespace chtest
{
	// Registers the fixture into the 'registry'
	CPPUNIT_TEST_SUITE_REGISTRATION( vertexchooserTest );

	//--------------------------------------------------------------------------

	void vertexchooserTest::setUp()
	{
	}

	void vertexchooserTest::tearDown()
	{
	}

	//--------------------------------------------------------------------------

	void vertexchooserTest::testCollectionWithPointers()
	{
		ch::collection<int*/*, ch::single_deleter*/> c {new int(5), new int(4), new int(3)};

		CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), c.size() );
		CPPUNIT_ASSERT_EQUAL( 5, *c[0] );
		CPPUNIT_ASSERT_EQUAL( 4, *c[1] );
		CPPUNIT_ASSERT_EQUAL( 3, *c[2] );
	}

	//--------------------------------------------------------------------------

	void vertexchooserTest::testCollectionWithValueType()
	{
		ch::collection<int, ch::nop_deleter> c {5, 4, 3};

		CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), c.size() );
		CPPUNIT_ASSERT_EQUAL( 5, c[0] );
		CPPUNIT_ASSERT_EQUAL( 4, c[1] );
		CPPUNIT_ASSERT_EQUAL( 3, c[2] );
	}

	//--------------------------------------------------------------------------

	void vertexchooserTest::testCollectionWithPointersToObject()
	{
		ch::collection<ch::vertexchooserrule<float>*> ruleCollection {	 new ch::vertexchooserrule1st<float>
																		,new ch::vertexchooserrule1st<float> };
		float vertexarr[] = { 3, 4, 5 };
		std::unique_ptr<ch::dataholder<float>> dh = ch::getDataHolder<float>( vertexarr, 0, 0, 1 );

		ch::tetrahedronverticeschooser<float> thVerticesChooser( *dh.get() );
		ch::vertexchooser<float> &vertexChooser = thVerticesChooser;

		std::vector<ch::vid_t> resultVertices;
		vertexChooser.chooseVertices( ruleCollection, resultVertices );

		CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), ruleCollection.size() );
	}

	//--------------------------------------------------------------------------

}
