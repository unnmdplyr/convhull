

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

	void vertexproviderTest::testDataHolderCheckDataPart()
	{
		std::vector<float> vertices = {1,2,3,4,5,6};
		std::unique_ptr<ch::dataholder<float>> dh  = ch::getDataHolder<float>( &vertices[0], 0, 3*sizeof(float), 2 );

		size_t expVal = 2;
		CPPUNIT_ASSERT_EQUAL( expVal, dh->size() );

		for ( size_t i=0; i < dh->size(); ++i )
		{
			auto vd = dh->operator[](i);
			CPPUNIT_ASSERT_EQUAL( vertices[3*i+0], vd.x );
			CPPUNIT_ASSERT_EQUAL( vertices[3*i+1], vd.y );
			CPPUNIT_ASSERT_EQUAL( vertices[3*i+2], vd.z );
		}
	}

	void vertexproviderTest::testDataHolderCheckPadding()
	{
		struct paddedvertex
		{
			float x;	int pad10; size_t pad11;
			float y;	int pad20; size_t pad21;
			float z;	int pad30; size_t pad31;
									size_t pad32;
									size_t pad33;
									size_t pad34;
		};

		paddedvertex pv0 = { 1, 0, 0, 2, 0, 0, 3, 0, 0, 0, 0, 0 };
		paddedvertex pv1 = { 4, 0, 0, 5, 0, 0, 6, 0, 0, 0, 0, 0 };

		std::vector<paddedvertex> vertices = {pv0, pv1};
		std::unique_ptr<ch::dataholder<float>> dh
								= ch::getDataHolder<float>(
												reinterpret_cast<float*>(&vertices[0])
												,sizeof(int)+sizeof(size_t)
												,3*(sizeof(float)+sizeof(int)) + 6*sizeof(size_t), 2 );
		size_t expVal = 2;
		CPPUNIT_ASSERT_EQUAL( expVal, dh->size() );

		for ( size_t i=0; i < dh->size(); ++i )
		{
			auto vd = dh->operator[](i);
			CPPUNIT_ASSERT_EQUAL( vertices[i].x, vd.x );
			CPPUNIT_ASSERT_EQUAL( vertices[i].y, vd.y );
			CPPUNIT_ASSERT_EQUAL( vertices[i].z, vd.z );
		}
	}
}
