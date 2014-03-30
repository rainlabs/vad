/*
 * File:   MFCCTest.h
 * Author: rain
 *
 * Created on 30.03.2014, 19:28:27
 */

#ifndef MFCCTEST_H
#define	MFCCTEST_H

#define UNIT_TEST
class MFCCTest;

#include <cppunit/extensions/HelperMacros.h>
#include "mfcc.h"

class MFCCTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(MFCCTest);

    CPPUNIT_TEST(testInitialize);
    CPPUNIT_TEST(testExtract);

    CPPUNIT_TEST_SUITE_END();

public:
    MFCCTest();
    virtual ~MFCCTest();
    void setUp();
    void tearDown();

private:
    void testInitialize();
    void testExtract();
};

#endif	/* MFCCTEST_H */

