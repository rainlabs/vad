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
#include <iostream>
#include <math.h>
#include "test_helper.h"
#include "mfcc.h"

class MFCCTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(MFCCTest);

    CPPUNIT_TEST(testInitialize);
    CPPUNIT_TEST(testSignalRead);
    CPPUNIT_TEST(testDFT);
    CPPUNIT_TEST(testTrifBank);
    CPPUNIT_TEST(testExtract);

    CPPUNIT_TEST_SUITE_END();

public:
    MFCCTest();
    virtual ~MFCCTest();
    void setUp();
    void tearDown();

private:
    MFCC* mfcc;
    void testInitialize();
    void testCustomInitialize();
    void testSignalRead();
    void testExtract();
    void testDFT();
    void testTrifBank();
};

#endif	/* MFCCTEST_H */

