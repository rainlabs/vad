#ifndef MFCC_H
#define MFCC_H

#include <string>
#include <vector>
#include <complex>
#include <fftw3.h>      // FFT and DCT transform
//#include <Eigen/Dense>  // Matrix logic
#include <iostream> // TODO: remove
#include <math.h>
#include "signal.h"
#define Malloc(type,n) (type *)fftw_malloc((n)*sizeof(type)) // from svm_train.c

typedef std::vector< std::vector<double> > vector2d;

class MFCC
{
public:
    #ifdef UNIT_TEST
    friend class MFCCTest;
    #endif

    MFCC(int duration = 30, int filtersCount = 32, int mfccCount = 16);
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
    vector2d extract();

//protected:
    double hzToMel(double hz);
    double melToHz(double mel);
    
    /**
     * @brief Split stram by interval ms and apply DFT based on libFFTW3
     * @param ms as frame length in ms
     * @return spectral flatness energy
     */
    vector2d dft();
    
    /**
     * @brief get triangle filter coefficients
     * @return filtersCount*mFftSize/2
     */
    vector2d trifBank();
    
    void initialize(int duration, int filtersCount, int mfccCount);

private:
    Signal * mStream;
    size_t   mFiltersCount;
    size_t   mMfccCount;
    size_t   mDuration;
    size_t   mFftSize;
};

#endif // MFCC_H
