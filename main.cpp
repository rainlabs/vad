#include <exception>
#include <stdio.h>
#include "mfcc.h"
#include "c_svm.h"
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    MFCC * mfcc;
    char* filename = new char(100);
    if (argc == 2) {
        mfcc = new MFCC(argv[1]);
    } else {
        mfcc = new MFCC("/home/rain/master/signal_examples/voiced_temp/1 (3).wav");
//        mfcc = new MFCC("/home/rain/master/signal_examples/unvoiced_temp/kitai-forever (4).wav");
    }

//    SVM * machine = new SVM(15);
    std::vector< std::vector<double> > voicedFeatures, temp;
//    std::vector<int> flags;

//    struct dirent *ent;
//    DIR *dir;
//    if ((dir = opendir ("/home/rain/master/signal_examples/voiced")) != NULL) {
//        while ((ent = readdir (dir)) != NULL) {
//            if (ent->d_type != DT_DIR) {
//                strcpy(filename, "/home/rain/master/signal_examples/voiced/");
//                strcat(filename, ent->d_name);
//                mfcc = new MFCC(filename);
//                temp = mfcc->extract();
//                voicedFeatures.insert(voicedFeatures.begin(), temp.begin(), temp.end());
//                for(int i = 0; i < temp.size(); i++) {
//                    flags.push_back(1);
//                }
//            }
//        }
//        closedir (dir);
//    }

//    if ((dir = opendir ("/home/rain/master/signal_examples/unvoiced")) != NULL) {
//        while ((ent = readdir (dir)) != NULL) {
//            if (ent->d_type != DT_DIR) {
//                strcpy(filename, "/home/rain/master/signal_examples/unvoiced/");
//                strcat(filename, ent->d_name);
//                mfcc = new MFCC(filename);
//                temp = mfcc->extract();
//                voicedFeatures.insert(voicedFeatures.begin(), temp.begin(), temp.end());
//                for(int i = 0; i < temp.size(); i++) {
//                    flags.push_back(-1);
//                }
//            }
//        }
//        closedir (dir);
//    }
//    machine->train(voicedFeatures, flags);

    temp = mfcc->extract();
    SVM * machine = new SVM(15);
    machine->load();
    int i, n = 0;

    for(i = 0; i < temp.size(); i++) {
        std::cout << machine->recognize(temp[i]) << std::endl;
        if (machine->recognize(temp[i]) > 0) {
            n++;
        }
    }

    std::cout << "count: " << i << std::endl;
    std::cout << "voice count: " << n << std::endl;
    std::cout << "percent: " << (float) n / (float) i * 100 << std::endl;


//    std::vector< std::vector<double> > features = mfcc->extract();
//    machine->train(features, 1);
//    FILE * file = fopen("/home/rain/master/v1.pcm", "wb");
//    for(int i = 0; i < features.size(); i++) {
//        fwrite(features[i].data(), sizeof(features[i][0]), sizeof(features[i].data()), file);
//    }
//    fclose(file);

//    delete machine;
//    delete mfcc;
    return 0;
}
