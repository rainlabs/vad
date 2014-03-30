/*
 * File:   MFCCTest.cpp
 * Author: rain
 *
 * Created on 30.03.2014, 19:28:27
 */

#include "MFCCTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(MFCCTest);

MFCCTest::MFCCTest() {
}

MFCCTest::~MFCCTest() {
}

void MFCCTest::setUp() {
}

void MFCCTest::tearDown() {
}

void MFCCTest::testInitialize() {
    MFCC* mfcc = new MFCC();
    CPPUNIT_ASSERT(mfcc->mWindowSize   == 512);
    CPPUNIT_ASSERT(mfcc->mOverlapSize  == 256);
    CPPUNIT_ASSERT(mfcc->mFiltersCount == 32);
    CPPUNIT_ASSERT(mfcc->mMfccCount    == 16);
    CPPUNIT_ASSERT(mfcc->mStream       == nullptr);
    
    mfcc->load("tests/fixtures/voice1.wav");
    
    CPPUNIT_ASSERT(mfcc->mStream       != nullptr);
    CPPUNIT_ASSERT(mfcc->mStream->getSampleRate() == 9600);
}

void MFCCTest::testCustomInitialize() {
    MFCC* mfcc = new MFCC(256, 128, 64, 20);
    CPPUNIT_ASSERT(mfcc->mWindowSize   == 256);
    CPPUNIT_ASSERT(mfcc->mOverlapSize  == 128);
    CPPUNIT_ASSERT(mfcc->mFiltersCount == 64);
    CPPUNIT_ASSERT(mfcc->mMfccCount    == 20);
    CPPUNIT_ASSERT(mfcc->mStream       == nullptr);
}

void MFCCTest::testExtract() {
    MFCC* mfcc = new MFCC();
    mfcc->load("tests/fixtures/voice1.wav");
    CPPUNIT_ASSERT(mfcc->mStream->getSampleRate() == 9600);
    
    auto features = mfcc->extract();
    
    CPPUNIT_ASSERT(features.size() != 0);
    for(auto feature: features) {
        CPPUNIT_ASSERT(feature.size() == 16);
    }
}

