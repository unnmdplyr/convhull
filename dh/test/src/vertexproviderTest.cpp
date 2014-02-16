

#include "vertexproviderTest.h"


//	---- only to printout
#include <iostream>
using std::cout;
using std::endl;
//	---- only to printout

namespace chtest
{
	// Registers the fixture into the 'registry'
	CPPUNIT_TEST_SUITE_REGISTRATION( vertexproviderTest );

	//--------------------------------------------------------------------------

	void vertexproviderTest::setUp()
	{
	}

	void vertexproviderTest::tearDown()
	{
	}

	//--------------------------------------------------------------------------

	void vertexproviderTest::testSetLessOperator()
	{
		CPPUNIT_ASSERT_EQUAL( 1, 1 );
	}
}
