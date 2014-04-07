#ifndef VMFCC_H
#define VMFCC_H

#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include <fftw3.h>      // FFT and DCT transform
//#include <Eigen/Dense>  // Matrix logic
#include <iostream> // TODO: remove
#include <math.h>
#include "signal.h"
#include "window.h"
#define Malloc(type,n) (type *)fftw_malloc((n)*sizeof(type)) // from svm_train.c

typedef std::vector< std::vector<double> > vector2d;

class MFCC
{
public:
    #ifdef UNIT_TEST
    friend class MFCCTest;
    #endif

    enum WINDOW {
        HAMMING,
        BLACKMAN_HARRIS,
        HANN
    };

    MFCC(int duration = 30, int overlap = 15, int filtersCount = 24, int mfccCount = 16, int window = 0);
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
    
    /**
     * @brief dft * trifBank
     * @return preMFCC
     */
    vector2d dftOnTrifBank();

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
    
    std::vector<double> dct(std::vector<double> x);
    
protected:
    
    void initialize(int duration, int overlap, int filtersCount, int mfccCount, int window);

private:
    Signal * mStream;
    size_t   mFiltersCount;
    size_t   mMfccCount;
    size_t   mDuration;
    size_t   mFftSize;
    size_t   mOverlapSize;
    int      mWindowType;
};

#endif // VMFCC_H
