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
    CPPUNIT_ASSERT(mfcc->mDuration     == 30);
    CPPUNIT_ASSERT(mfcc->mFiltersCount == 32);
    CPPUNIT_ASSERT(mfcc->mMfccCount    == 16);
    CPPUNIT_ASSERT(mfcc->mStream       != nullptr);
    CPPUNIT_ASSERT(mfcc->mStream->getSampleRate() == 22050);
}

void MFCCTest::testExtract() {
    std::string filename = "gnuplot_mfcc";
    int duration = mfcc->mDuration / 2;
    auto out = mfcc->dftOnTrifBank();
    std::vector<float> x, y;
    int i;
    float t;
    
    for(i = 0; i < out.size(); i++)
        x.push_back( i*duration / 1000. );
    std::cout << x.back() << std::endl;
    for(i = 0; i < out.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(out, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void MFCCTest::testDFT() {
    std::string filename = "gnuplot_fft";
    int duration = mfcc->mDuration / 2;
    float hzInterval = 1000.0 / duration;
    auto dft = mfcc->dft();
    std::vector<float> x, y;
    int i;
    float t;
    
    for(i = 0; i < dft.size(); i++) {
        for(int j = 0; j < dft[i].size(); j++) {
            dft[i][j] = log(dft[i][j]);
        }
    }
    
    for(i = 0; i < dft.size(); i++)
        x.push_back( i*duration / 1000. );
    for(i = 0; i < dft.back().size(); i++)
        y.push_back( i*hzInterval );
    
    TestHelper::saveMatrix(dft, x, y, filename);
    TestHelper::plotMatrix(filename);
    /* FIXME: need to remove after plot*/
//    remove((filename + ".dat").data());
}

void MFCCTest::testTrifBank() {
    std::string filename = "gnuplot_trifbank";
    auto tb = mfcc->trifBank();
    float hzInterval = 1000.0 / mfcc->mDuration;
    std::vector<float> x, y;
    float t;
    int i;
    
    for(i = 0; i < tb.back().size(); i++) {
        x.push_back( i*hzInterval );
    }
    
    TestHelper::savePoints(tb, x, filename);
    TestHelper::plotPoints(filename);
}

void MFCCTest::testSignalRead() {
    FILE* file = fopen("tests/fixtures/matlab/mike.pcm", "rb");
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
