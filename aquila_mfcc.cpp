#include <aquila/aquila.h>

#include <string>
#include <stdio.h>
#include "tests/test_helper.h"
#include "vendor/gnuplot.hpp"

unsigned int gFftSize = 256;
unsigned int gMfccCount = 12;
unsigned int gOverlapSize = 128;
std::string gFile = "";
std::string gDir = "result/";

void processArguments(int argc, char *argv[]);
void aquilaMfcc(std::string filename);

int main(int argc, char* argv[]) {
    processArguments(argc, argv);
    
    aquilaMfcc( (gDir + "3aquila_mfcc") );
    
    return 0;
}

void processArguments(int argc, char *argv[]) {
    char* s1;
    
    if (argc <= 1) {
        fprintf(stderr, "arguments are not found\n");
        exit(1);
    }
    
    for(int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != 0) {
            s1 = "";
            if (i + 1 >= argc) {
                fprintf(stderr, "not valid argument %s\n", argv[i]);
                exit(2);
            }
            s1 = argv[i + 1];
            switch (argv[i][1]) {
                case 'd':
                    gDir = s1;
                    break;
                case 'f':
                    gFftSize = atoi(s1);
                    break;
                case 'o':
                    gOverlapSize = atoi(s1);
                    break;
                case 'm':
                    gMfccCount = atoi(s1);
                    break;
            }
        } else {
            gFile = argv[i];
        }
    }
    
    if (gFile.size() == 0) {
        fprintf(stderr, "filename is not specified\n");
        exit(3);
    }
}

void aquilaMfcc(std::string filename) {
    std::vector<float> x, y;
    std::vector< std::vector<double> > out;
    int i;
    
    Aquila::WaveFile wav(gFile);
    
    int N = wav.getSamplesCount();
    double raw[N];
    for (i = 0; i < N; i++) {
        raw[i] = wav.sample(i) / 32767.0; // int16 to double
    }
    Aquila::SignalSource s(raw, N);
    s.setSampleFrequency(wav.getSampleFrequency());
    
    Aquila::FramesCollection frames(s, gFftSize, gOverlapSize); 
    Aquila::Mfcc aMfcc(gFftSize); 
    
    for (Aquila::Frame& frame : frames) { 
        out.push_back( aMfcc.calculate(frame) );
    }
    
    for(i = 0; i < out.size(); i++)
        x.push_back( i*gOverlapSize );
    for(i = 0; i < out.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(out, x, y, filename);
    TestHelper::plotMatrix(filename);
}