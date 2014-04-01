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
    mfcc = new MFCC();
    mfcc->load("tests/fixtures/voice1.wav");
}

void MFCCTest::tearDown() {
    delete mfcc;
}

void MFCCTest::testInitialize() {
    CPPUNIT_ASSERT(mfcc->mWindowSize   == 512);
    CPPUNIT_ASSERT(mfcc->mOverlapSize  == 256);
    CPPUNIT_ASSERT(mfcc->mFiltersCount == 32);
    CPPUNIT_ASSERT(mfcc->mMfccCount    == 16);
    CPPUNIT_ASSERT(mfcc->mStream       != nullptr);
    CPPUNIT_ASSERT(mfcc->mStream->getSampleRate() == 9600);
}

void MFCCTest::testExtract() {
    CPPUNIT_ASSERT(mfcc->mStream->getSampleRate() == 9600);
    
//    auto features = mfcc->extract();
//    
//    CPPUNIT_ASSERT(features.size() != 0);
//    for(auto feature: features) {
//        CPPUNIT_ASSERT(feature.size() == 16);
//    }
}

void MFCCTest::testDFT() {
    std::string filename = "gnuplot_fft";
    int ms = 20;
    auto dft = mfcc->dft(ms);
    int i = 0;
    float t = 0;
    float n = dft.size();
    float hzInterval = 1000.0 / ms;
    
    Gnuplot g;
    FILE * file = fopen((filename + ".dat").data(), "wb");
    fwrite(&n, sizeof(float), 1, file);
    for(i = 0; i < dft.size(); i++) {
        fwrite(&t, sizeof(float), 1, file);
        t += ms / 1000.0;
    }
    t = 0;
    for(i = 0; i < dft[0].size(); i++) {
        fwrite(&t, sizeof(float), 1, file);
        t = (i+1) * hzInterval;
        for(auto list : dft) {
            float val = std::abs(list[i]);
            fwrite(&val, sizeof(float), 1, file);
        }
    }
    fclose(file);
    g.cmd("set terminal png size 1920, 1080");
    g.cmd(("set output \"" + filename + ".png\""));
    g.cmd( ("plot \"" + filename + ".dat\" binary matrix with image") );
    /* FIXME: need to remove after plot*/
//    remove((filename + ".dat").data());
}

void MFCCTest::testSignalRead() {
    FILE* file = fopen("tests/fixtures/matlab/voice1.pcm", "rb");
    double* val = new double;
    double* matlabVal = new double;
    mfcc->mStream->rewind();
    while( mfcc->mStream->readNext(val) != 0 ) {
        fread(matlabVal, sizeof(double), 1, file);
        CPPUNIT_ASSERT(*val == *matlabVal);
    }
    mfcc->mStream->rewind();
    fclose(file);
}
