

#include <vector>
#include "vertexproviderTest.h"

#include "dataholder_impl.h"

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

	void vertexproviderTest::testCreateDataHolder()
	{
		std::vector<float> vertices = {1,2,3,4,5,6};
		ch::dataholder<float>& firstDH  = ch::getDataHolder<float>( &vertices[0], 0, 3*sizeof(float), 2 );
		ch::dataholder<float>& secondDH = ch::getDataHolder<float>( &vertices[0], 0, 3*sizeof(float), 2 );

		CPPUNIT_ASSERT_EQUAL( &firstDH, &secondDH );
	}
}
