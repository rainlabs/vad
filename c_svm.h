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
    SVM(const char* filename = nullptr);
    SVM(int num_features, const char* filename = nullptr);

    void load();

    int train( std::vector< std::vector<double> > data, std::vector<double> cls);

protected:
    void initialize(int num_features, const char* filename);
    struct svm_problem* problemInitialize(int num_training_data);

    const char* defaultFileName()
    {
        return (const char*) "svm_db.dat";
    }

private:
    struct svm_parameter mParam;
    struct svm_model*    mModel;
    int                  mFeaturesCount;
    const char*          mFileName;
};

#endif // SVM_H
