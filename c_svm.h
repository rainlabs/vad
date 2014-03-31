/**
  * Support Vector Machine
  * based on libSVM http://www.csie.ntu.edu.tw/~cjlin/libsvm/
  */

#ifndef SVM_H
#define SVM_H

#include <svm.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#define Malloc(type,n) (type *)malloc((n)*sizeof(type)) // from svm_train.c

class SVM
{
public:
    #ifdef UNIT_TEST
    friend class SVMTest;
    #endif

    SVM(int num_features, const char* filename = "svm_db.dat");
    virtual ~SVM();

    void load();

    int train( std::vector< std::vector<double> > data, std::vector<int> cls);
    double recognize( std::vector<double> input );

protected:
    void initialize(int num_features, const char* filename);
    struct svm_problem* problemInitialize(int num_training_data);

private:
    void cleanModel();

    struct svm_parameter mParam;
    struct svm_model*    mModel;
    int                  mFeaturesCount;
    const char*          mFileName;
};

#endif // SVM_H
