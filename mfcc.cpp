#include "mfcc.h"

//public:
MFCC::MFCC(int windowSize, int overlapSize, int filtersCount, int mfccCount) {
    initialize(windowSize, overlapSize, filtersCount, mfccCount);
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

    std::cout << "file info:" << std::endl;
    std::cout << "file name: " << filename << std::endl;
    std::cout << "channels: " << mStream->getChannelCount() << std::endl;
    std::cout << "sample rate: " << mStream->getSampleRate() << std::endl;
    std::cout << "sample count: " << mStream->getSampleCount()  << std::endl;
}

std::vector< std::vector<double> > MFCC::extract()
{
    std::vector<double> s, f_smp;
    std::vector< std::vector<double> > S, P, X, C_ret;
    int i, k, j, n, m, M, N;
    M = mWindowSize / 2;
    N = mWindowSize;

    double* val = new double;
    while( mStream->readNext(val) != 0 ) {
        s.push_back( *val );
    }
    mStream->rewind();

    // add to full frame size
    n = mWindowSize - (s.size() % mWindowSize);
    for(i = 0; i < n; i++) {
        s.push_back(0.0);
    }

    int prev = mOverlapSize;
    for(i = 0; i < (s.size() / mOverlapSize - 1); i++) {
        prev += mOverlapSize;
        S.push_back( std::vector<double>(s.begin() + prev - mWindowSize, s.begin() + prev ) );
    }

    for(n = 0; n < S.size(); n++) {
        std::vector<double> A;
        for(k = 0; k < M; k++) {
            double sumRe = 0, sumIm = 0;;
            for(i = 0; i < N; i++) {
                sumRe += S[n][i] * cos( 2.0 * M_PI * (k + 1.0) * (double)i/N  );
                sumIm += S[n][i] * sin( 2.0 * M_PI * (k + 1.0) * (double)i/N  );
            }
            A.push_back( pow((2.0 / N) * sumRe, 2.0) + pow((-2.0 / N) * sumIm, 2.0) );
        }
        P.push_back( A );
    }
    double fMelLow  = hzToMel(0.0);
    double fMelHigh = hzToMel( mStream->getSampleRate() / 2.0 );
    double len = (fMelHigh - fMelLow) / (mFiltersCount + 1.0);

    for(i = 0; i < mFiltersCount; i++) {
        f_smp.push_back( melToHz(fMelLow + (i+1.) * len) * M / (double) mStream->getSampleRate() );
    }
    // --check it---

    for(n = 0; n < P.size(); n++) {
        std::vector<double> x_n;
        for(i = 0; i < mFiltersCount; i++) {
            double sum = 0;
            for(k = 0; k < M; k++) {
                double H = 0;
                if ((i != 0) && (f_smp[i-1] <= k) && (k <= f_smp[i])) {
                    H = (k - f_smp[i-1]) / (f_smp[i] - f_smp[i-1]);
                } else if ((i != mFiltersCount-1) && (f_smp[i] <= k) && (k <= f_smp[i+1])) {
                    H = (f_smp[i+1] - k) / (f_smp[i+1] - f_smp[i]);
                }

                sum += P[n][k] * H;
            }
            x_n.push_back( log(sum) );
        }
        X.push_back( x_n );
    }

    for(n = 0; n < X.size(); n++) {
        std::vector<double> c_n;
        // FIXME j = 0 for first coefficient
        for(j = 0; j < mMfccCount; j++) {
            double sum = 0;
            for(k = 0; k < mFiltersCount; k++) {
                // j instead j + 1
                sum += X[n][k] * cos( j * (k + 0.5) * M_PI / mFiltersCount );
            }
            c_n.push_back( sum );
        }
        C_ret.push_back(c_n);
    }

    for(i = 0; i < C_ret.size(); i++) {
        std::cout << "row " << i << ": ";
        for(j = 0; j < C_ret[i].size(); j++) {
            std::cout << C_ret[i][j] << ",";
        }
        std::cout << std::endl;
    }

    return C_ret;
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

void MFCC::initialize(int windowSize, int overlapSize, int filtersCount, int mfccCount)
{
    mFiltersCount = filtersCount;
    mMfccCount    = mfccCount;
    mWindowSize   = windowSize;
    mOverlapSize  = overlapSize;
    mStream       = nullptr;
}

//private:
