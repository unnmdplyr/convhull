
#ifndef VERTEXCHOOSERTEST_H_
#define VERTEXCHOOSERTEST_H_

#include <cppunit/extensions/HelperMacros.h>


namespace chtest
{
	class vertexchooserTest: public CppUnit::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE( vertexchooserTest );
		CPPUNIT_TEST( testCollectionWithValueType			);
		CPPUNIT_TEST( testCollectionWithPointers			);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testCollectionWithValueType();
		void testCollectionWithPointers();
	};
}

#endif /* VERTEXPROVIDERTEST_H_ */
