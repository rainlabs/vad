/* 
 * File:   SVMTest.h
 * Author: rain
 *
 * Created on 31 марта 2014 г., 12:37
 */

#ifndef SVMTEST_H
#define	SVMTEST_H

#define UNIT_TEST
class SVMTest;

#include <cppunit/extensions/HelperMacros.h>
#include <string.h>
#include "c_svm.h"

class SVMTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(SVMTest);

    CPPUNIT_TEST(testInitialize);
    CPPUNIT_TEST(testCustomInitialize);

    CPPUNIT_TEST_SUITE_END();

public:
    SVMTest();
    virtual ~SVMTest();
    void setUp();
    void tearDown();

private:
    void testInitialize();
    void testCustomInitialize();
};

#endif	/* SVMTEST_H */

