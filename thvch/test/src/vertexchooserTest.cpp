

#include <vector>
#include "vertexchooserTest.h"

#include "collection_impl.h"

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
		ch::collection<int*/*, ch::single_deleter*/> c;
		c.push_back( new int(5) );
		c.push_back( new int(4) );
		c.push_back( new int(3) );

		CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), c.size() );
	}

	//--------------------------------------------------------------------------

	void vertexchooserTest::testCollectionWithValueType()
	{
		ch::collection<int, ch::nop_deleter> c;
		c.push_back( 5 );
		c.push_back( 4 );
		c.push_back( 3 );

		CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), c.size() );
	}

	//--------------------------------------------------------------------------

}
