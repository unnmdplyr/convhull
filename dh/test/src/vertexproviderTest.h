
#ifndef VERTEXPROVIDERTEST_H_
#define VERTEXPROVIDERTEST_H_

#include <cppunit/extensions/HelperMacros.h>


namespace chtest
{
	class vertexproviderTest: public CppUnit::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE( vertexproviderTest );
		CPPUNIT_TEST( testSetLessOperator				);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testSetLessOperator();
	};
}

#endif /* VERTEXPROVIDERTEST_H_ */
