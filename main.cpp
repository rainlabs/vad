#include <exception>
#include <stdio.h>
#include "mfcc.h"
#include "c_svm.h"

int main(int argc, char *argv[])
{
    MFCC * mfcc;
    if (argc == 2) {
        mfcc = new MFCC(argv[1]);
    } else {
        mfcc = new MFCC("/home/rain/master/signals/voice1.wav");
    }

    SVM * machine = new SVM(16);

    std::vector< std::vector<double> > features = mfcc->extract();
//    machine->train(features, 1);
//    FILE * file = fopen("/home/rain/master/v1.pcm", "wb");
//    for(int i = 0; i < features.size(); i++) {
//        fwrite(features[i].data(), sizeof(features[i][0]), sizeof(features[i].data()), file);
//    }
//    fclose(file);

    delete machine;
    delete mfcc;
    return 0;
}
