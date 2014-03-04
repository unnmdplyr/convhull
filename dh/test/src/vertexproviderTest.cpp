

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

	//	Checks whether only one dataholder is created by the getDataHolder() function.
	void vertexproviderTest::testCreateDataHolder()
	{
		std::vector<float> vertices = {1,2,3,4,5,6};
		ch::dataholder<float>& firstDH  = ch::getDataHolder<float>( &vertices[0], 0, 3*sizeof(float), 2 );
		ch::dataholder<float>& secondDH = ch::getDataHolder<float>( &vertices[0], 0, 3*sizeof(float), 2 );

		CPPUNIT_ASSERT_EQUAL( &firstDH, &secondDH );
	}

	void vertexproviderTest::testDataHolderCheckDataPart()
	{
		std::vector<float> vertices = {1,2,3,4,5,6};
		ch::dataholder<float>& dh  = ch::getDataHolder<float>( &vertices[0], 0, 3*sizeof(float), 2 );

		size_t expVal = 2;
		CPPUNIT_ASSERT_EQUAL( expVal, dh.size() );

		for ( size_t i=0; i < dh.size(); ++i )
		{
			auto vd = dh[i];
			CPPUNIT_ASSERT_EQUAL( vertices[3*i+0], vd.x );
			CPPUNIT_ASSERT_EQUAL( vertices[3*i+1], vd.y );
			CPPUNIT_ASSERT_EQUAL( vertices[3*i+2], vd.z );
		}
	}

}
