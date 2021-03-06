
#ifndef VERTEXPROVIDERTEST_H_
#define VERTEXPROVIDERTEST_H_

#include <cppunit/extensions/HelperMacros.h>


namespace chtest
{
	class vertexproviderTest: public CppUnit::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE( vertexproviderTest );
		CPPUNIT_TEST( testDataHolderCheckDataPart		);
		CPPUNIT_TEST( testDataHolderCheckPadding		);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testDataHolderCheckDataPart();
		void testDataHolderCheckPadding();
	};
}

#endif /* VERTEXPROVIDERTEST_H_ */
