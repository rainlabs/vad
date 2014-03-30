#ifndef MFCC_H
#define MFCC_H

#include <string>
#include <iostream>
#include <math.h>
#include "signal.h"

class MFCC
{
public:
    #ifdef UNIT_TEST
    friend MFCCTest;
    #endif

    MFCC(int windowSize = 512, int overlapSize = 256, int filtersCount = 32, int mfccCount = 16);
    virtual ~MFCC();

    /**
     * @brief load sound file
     * @param filename
     */
    void load(std::string filename);

    /**
     * @brief extract MFCC features
     * @return 
     */
    std::vector< std::vector<double> > extract();

protected:
    double freqToMel(double f);
    double melToFreq(double m);
    void initialize(int windowSize, int overlapSize, int filtersCount, int mfccCount);

private:
    Signal * mStream;
    size_t   mFiltersCount;
    size_t   mMfccCount;
    size_t   mWindowSize;
    size_t   mOverlapSize;
};

#endif // MFCC_H
