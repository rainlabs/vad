#include "mfcc.h"

//public:
MFCC::MFCC(int duration, int overlap, int filtersCount, int mfccCount, int window) {
    initialize(duration, overlap, filtersCount, mfccCount, window);
}

MFCC::~MFCC() {
    if (mStream != nullptr)
        delete mStream;
}

void MFCC::load(std::string filename)
{
    if (mStream != nullptr)
        delete mStream;
    
    mStream = new Signal();
    mStream->loadFromFile(filename);
    mFftSize = mStream->getSampleRate() * mDuration / 1000.0;
    mOverlapSize = mStream->getSampleRate() * mOverlapSize / 1000.0;

    std::cout << "file info:" << std::endl;
    std::cout << "file name: " << filename << std::endl;
    std::cout << "channels: " << mStream->getChannelCount() << std::endl;
    std::cout << "sample rate: " << mStream->getSampleRate() << std::endl;
    std::cout << "sample count: " << mStream->getSampleCount()  << std::endl;
}

vector2d MFCC::extract()
{
    int k, j;
    auto X = dftOnTrifBank();
    vector2d ret;
    
    for(auto x_n : X) {
//        std::vector<double> vec;
//        for(j = 0; j < mMfccCount; j++) {
//            double sum = 0;
//            for(k = 0; k < mFiltersCount; k++) {
//                sum += x_n[k] * cos( (double) j * ( (double) k + 0.5) * M_PI / mFiltersCount );
//            }
//            vec.push_back(sum);
//        }
//        std::vector<double> tst = dct(x_n);
//        ret.push_back(vec);
//        std::vector<double> vec = dct(x_n);
//        double mean = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
//        std::for_each( vec.begin(), vec.end(), [&](double &el) {
//            el -= mean; 
//        });
//        ret.push_back( vec );
        ret.push_back( dct(x_n) );
    }
    
    return ret;
}

vector2d MFCC::dftOnTrifBank() {
    int k;
    auto P = dft();
    auto H = trifBank();
    vector2d X;
    
    for(auto p_n : P) {
        std::vector<double> vec;
        for(auto h_i : H) {
            double sum = 0;
            for(k = 0; k < p_n.size(); k++) {
                sum += pow(p_n[k], 2) * h_i[k];
            }
            vec.push_back(log(sum));
        }
        X.push_back( vec );
    }
    
    return X;
}

//protected:
double MFCC::hzToMel(double hz)
{
    return (1127.0 * log( 1.0 + hz / 700.0 ));
}

double MFCC::melToHz(double mel)
{
    return (700.0 * (exp( mel / 1127.0) - 1.0 ));
}

vector2d MFCC::dft() {
    fftw_complex *in, *out;
    fftw_plan plan;
    int i, j;
    double* val = new double;
    int step = mFftSize - mOverlapSize;
    vector2d ret;
    std::vector<double> samples, w;
    
    switch(mWindowType) {
        case MFCC::BLACKMAN_HARRIS:
            w = Window::blackmanHarris(mFftSize);
            break;
        case MFCC::HANN:
            w = Window::hann(mFftSize);
            break;
        case MFCC::HAMMING:
        default:
            w = Window::hamming(mFftSize);
            break;
    }
    
    in =  Malloc(fftw_complex, mFftSize);
    out = Malloc(fftw_complex, mFftSize);
    plan = fftw_plan_dft_1d(mFftSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    
    mStream->rewind();
    i = 0;
    while( mStream->readNext(val) != 0 ) {
        samples.push_back( *val );
    }
    mStream->rewind();
    int N = mFftSize - (samples.size() % mFftSize);
    for(i = 0; i < N; i++) {
        samples.push_back(0.);
    }
    // TODO <=
    for(i = 0; i < samples.size() - mFftSize; i+= step) {
        for(j = 0; j < mFftSize; j++) {
            in[j][0] = samples[i+j] * w[j];
            in[j][1] = 0;
        }
        fftw_execute(plan);
        std::vector< double > line;

        for(j = 0; j < mFftSize / 2; j++) {
            line.push_back( std::abs(std::complex<double>(out[j][0], out[j][1])) );
        }
        ret.push_back(line);
    }
    mStream->rewind();
    
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    
    return ret;
}

vector2d MFCC::trifBank() {
    float fLow = hzToMel(300.0);
    float fHigh = hzToMel(3700.0);
//    float fHigh = hzToMel(mStream->getSampleRate() / 2.);
    int M = mFftSize / 2;
    std::vector< double > C;
    float tmp, interval = 1000.0 / mDuration;
    float len = (fHigh - fLow) / (mFiltersCount + 1.);
    int i,k;
    vector2d ret;
    
    for(i = 0; i < mFiltersCount + 2; i++) {
        C.push_back( melToHz(fLow + i * len) );
    }
    
    for(i = 0; i < mFiltersCount; i++) {
        std::vector<double> vec;
        for(k = 0; k < M; k++) {
            tmp = k * interval;
            if (C[i] <= tmp && tmp <= C[i+1]) {
                vec.push_back( (tmp - C[i]) / (C[i+1] - C[i]) );
            } else if (C[i+1] <= tmp && tmp <= C[i+2]) {
                vec.push_back( (C[i+2] - tmp) / (C[i+2] - C[i+1]) );
            } else {
                vec.push_back(0.);
            }
        }
        ret.push_back( vec );
    }
    return ret;
}

std::vector<double> MFCC::dct(std::vector<double> x) {
    fftw_plan plan;
    int i, j, N = x.size();
    double* val = new double;
    std::vector<double> ret;
    double *in, *out;
    
    in =  Malloc(double, N);
    out = Malloc(double, N);
    plan = fftw_plan_r2r_1d(N, in, out, FFTW_REDFT10, FFTW_ESTIMATE);
    
    for(i = 0; i < N; i++) {
        in[i] = x[i];
    }
    
    fftw_execute(plan);
    
    for(i = 0; i < mMfccCount; i++) {
        ret.push_back(out[i] / 2.0);
    }
    
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    
    return ret;
}

void MFCC::initialize(int duration, int overlap, int filtersCount, int mfccCount, int window)
{
    mFiltersCount = filtersCount;
    mMfccCount    = mfccCount;
    mDuration     = duration;
    mStream       = nullptr;
    mFftSize      = 0;
    mOverlapSize  = overlap;
    mWindowType   = window;
}

//private:
