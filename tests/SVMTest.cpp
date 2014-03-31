/* 
 * File:   SVMTest.cpp
 * Author: rain
 * 
 * Created on 31 марта 2014 г., 12:37
 */

#include "SVMTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SVMTest);

SVMTest::SVMTest() {
}

SVMTest::~SVMTest() {
}

void SVMTest::setUp() {
}

void SVMTest::tearDown() {
}

void SVMTest::testInitialize() {
    SVM* svm = new SVM(16);
    CPPUNIT_ASSERT(svm->mFeaturesCount == 16);
    CPPUNIT_ASSERT(strcmp(svm->mFileName, "svm_db.dat") == 0);
    CPPUNIT_ASSERT(svm->mModel == nullptr);
    CPPUNIT_ASSERT(svm->mParam.gamma == (1. / 16.));
    CPPUNIT_ASSERT(svm->mParam.kernel_type == RBF);
    CPPUNIT_ASSERT(svm->mParam.svm_type == C_SVC);
}

void SVMTest::testCustomInitialize() {
    SVM* svm = new SVM(32, "filename.dat");
    CPPUNIT_ASSERT(svm->mFeaturesCount == 32);
    CPPUNIT_ASSERT(strcmp(svm->mFileName, "filename.dat") == 0);
    CPPUNIT_ASSERT(svm->mModel == nullptr);
    CPPUNIT_ASSERT(svm->mParam.gamma == (1. / 32.));
    CPPUNIT_ASSERT(svm->mParam.kernel_type == RBF);
    CPPUNIT_ASSERT(svm->mParam.svm_type == C_SVC);
}

