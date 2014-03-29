#include "c_svm.h"

SVM::SVM(const char* filename)
{
    mModel = nullptr;
    if (filename == nullptr)
        mFileName = defaultFileName();
    else
        mFileName = filename;

    load();
}

void SVM::load()
{
    if (mModel != nullptr)
        svm_free_and_destroy_model(&mModel);

    mModel = svm_load_model(mFileName);
}

SVM::SVM(int num_features, const char* filename)
{
    initialize(num_features, filename);
}

int SVM::train( std::vector< std::vector<double> > data, std::vector<double> cls)
{
    struct svm_node* xSpace;
    struct svm_problem* problem;
    int i, j, n = 0;
    const char* errorMsg;

    problem = problemInitialize( data.size() );
    xSpace = Malloc(struct svm_node, mFeaturesCount * problem->l + problem->l);

    for(i = 0; i < problem->l; i++)
    {
        problem->x[i] = &xSpace[n];
        problem->y[i] = cls[i];

        for(j = 0; j < mFeaturesCount; j++) {
            xSpace[n].index = j + 1;
            xSpace[n++].value = data[i][j];
        }
        xSpace[n++].index = -1;
    }

    errorMsg = svm_check_parameter(problem,&mParam);

    if(errorMsg)
    {
        fprintf(stderr,"ERROR: %s\n",errorMsg);
        return 1;
    }

    mModel = svm_train(problem,&mParam);

    if(svm_save_model(mFileName,mModel))
    {
        fprintf(stderr, "can't save model to file %s\n", mFileName);
        return 2;
    }

//    svm_free_and_destroy_model(&mModel);
//    mModel = nullptr;

//    for(i = 0; i < problem->l; i++) {
//        free(problem->x[i]);
//    }
//    free(problem->y);
//    free(problem->x);
//    free(problem);

    return 0;
}

//protected:

struct svm_problem* SVM::problemInitialize(int num_training_data)
{
    struct svm_problem* problem = Malloc(svm_problem,1);
    problem->l = num_training_data; // num training data
    problem->y = Malloc(double,problem->l);
    problem->x = Malloc(struct svm_node*,problem->l);
    return problem;
}

void SVM::initialize(int num_features, const char* filename)
{
    mModel = nullptr;
    mFeaturesCount = num_features;

    if (filename == nullptr)
        mFileName = defaultFileName();
    else
        mFileName = filename;

    // default values
    mParam.svm_type = C_SVC;
    mParam.kernel_type = RBF;
    mParam.degree = 3;
    mParam.gamma = 1. / mFeaturesCount;	// 1/num_features
    mParam.coef0 = 0;
    mParam.nu = 0.5;
    mParam.cache_size = 100;
    mParam.C = 1;
    mParam.eps = 1e-3;
    mParam.p = 0.1;
    mParam.shrinking = 1;
    mParam.probability = 0;
    mParam.nr_weight = 0;
    mParam.weight_label = nullptr;
    mParam.weight = nullptr;
//	cross_validation = 0;
}
