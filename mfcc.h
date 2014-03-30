#ifndef MFCC_H
#define MFCC_H

#include <string>
#include <iostream>
#include <math.h>
#include "signal.h"

class MFCC
{
public:
    MFCC();
    MFCC(std::string filename);

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

    size_t defaultFiltersCount() {
        return 32;
    }

    size_t defaultMfccCount() {
        return 16;
    }

    size_t defaultWindowSize() {
        return 512;
    }

    size_t defaultOverlapSize() {
        return 256;
    }

    void initialize(std::string filename);

private:
    Signal * mStream;
    size_t   mFiltersCount;
    size_t   mMfccCount;
    size_t   mWindowSize;
    size_t   mOverlapSize;
};

#endif // MFCC_H
