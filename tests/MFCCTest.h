/*
 * File:   MFCCTest.h
 * Author: rain
 *
 * Created on 30.03.2014, 19:28:27
 */

#ifndef MFCCTEST_H
#define	MFCCTEST_H

#include <cppunit/extensions/HelperMacros.h>

class MFCCTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(MFCCTest);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    MFCCTest();
    virtual ~MFCCTest();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* MFCCTEST_H */

