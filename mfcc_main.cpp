/* 
 * File:   MFCCMain.cpp
 * Author: rain
 * 
 * Created on 6 апреля 2014 г., 10:54
 */
#include <string>
#include <stdio.h>
#include "mfcc.h"
#include "tests/test_helper.h"
#include "vendor/gnuplot.hpp"

unsigned int gDuration = 30;
unsigned int gFiltersCount = 24;
unsigned int gMfccCount = 16;
unsigned int gOverlapSize = 15;
int gWindow = MFCC::HAMMING;
std::string gFile = "";
std::string gDir = "result/";
MFCC* mfcc = nullptr;

void processArguments(int argc, char *argv[]);
void dft(std::string filename);
void trifBank(std::string filename);
void dftOnTrifBank(std::string filename);
void mfccExtract(std::string filename);
void aquilaMfcc(std::string filename);

void progress(int percent) {
    std::cout << "\r" << percent << "% completed." << std::flush;
}

int main(int argc, char* argv[]) {
    processArguments(argc, argv);
    mfcc = new MFCC(gDuration, gOverlapSize, gFiltersCount, gMfccCount, gWindow);
    mfcc->load(gFile);
    progress(10);
    dft( (gDir + "1dft") );
    progress(25);
    trifBank( (gDir + "0trifbank") );
    progress(50);
    dftOnTrifBank( (gDir + "2pre_mfcc") );
    progress(75);
    mfccExtract( (gDir + "3mfcc") );
    progress(100);
    std::cout << std::endl;
    return 0;
}

/**
 * help:
 * -d = dir (default: "result/")
 * -f = filters count (default: 24)
 * -m = mfcc count (default: 16)
 * -t = duration (default: 30 ms)
 * -o = overlap size (default: 15 ms)
 * -w = window function (default: hamming) enum {HAMMING, BLACKMAN_HARRIS, HANN}
 * @param argc
 * @param argv
 */
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
                case 't':
                    gDuration = atoi(s1);
                    break;
                case 'd':
                    gDir = s1;
                    break;
                case 'f':
                    gFiltersCount = atoi(s1);
                    break;
                case 'm':
                    gMfccCount = atoi(s1);
                    break;
                case 'o':
                    gOverlapSize = atoi(s1);
                    break;
                case 'w':
                    gWindow = atoi(s1);
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

void dft(std::string filename) {
    int duration = gDuration - gOverlapSize;
    float hzInterval = 1000.0 / (gDuration / 2.0);
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
}

void trifBank(std::string filename) {
    auto tb = mfcc->trifBank();
    float hzInterval = 1000.0 / gDuration;
    std::vector<float> x;
    float t;
    int i;
    
    for(i = 0; i < tb.back().size(); i++) {
        x.push_back( i*hzInterval );
    }
    
    TestHelper::savePoints(tb, x, filename);
    TestHelper::plotPoints(filename);
}

void dftOnTrifBank(std::string filename) {
    int duration = gDuration - gOverlapSize;
    auto out = mfcc->dftOnTrifBank();
    std::vector<float> x, y;
    int i;
    float t;
    
    for(i = 0; i < out.size(); i++)
        x.push_back( i*duration / 1000. );
    for(i = 0; i < out.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(out, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void mfccExtract(std::string filename) {
    int duration = gDuration - gOverlapSize;
    auto out = mfcc->extract();
    std::vector<float> x, y;
    int i;
    float t;
    
    for(i = 0; i < out.size(); i++)
        x.push_back( i*duration / 1000. );
    for(i = 0; i < out.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(out, x, y, filename);
    TestHelper::plotMatrix(filename);
}