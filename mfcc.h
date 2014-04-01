#ifndef MFCC_H
#define MFCC_H

#include <string>
#include <vector>
#include <complex>
#include <fftw3.h>
#include <iostream> // TODO: remove
#include <math.h>
#include "signal.h"
#define Malloc(type,n) (type *)fftw_malloc((n)*sizeof(type)) // from svm_train.c

class MFCC
{
public:
    #ifdef UNIT_TEST
    friend class MFCCTest;
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
    double hzToMel(double hz);
    double melToHz(double mel);
    
    /**
     * @brief Split stram by ms and apply DFT based on libFFTW3
     * @param ms as frame length in ms
     * @return complex vectors
     */
    std::vector< std::vector< std::complex<double> > > dft(unsigned int ms=20);
    
    void initialize(int windowSize, int overlapSize, int filtersCount, int mfccCount);

private:
    Signal * mStream;
    size_t   mFiltersCount;
    size_t   mMfccCount;
    size_t   mWindowSize;
    size_t   mOverlapSize;
};

#endif // MFCC_H
