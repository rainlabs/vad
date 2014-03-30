/* 
 * File:   vad.h
 * Author: rain
 *
 * Created on 30 марта 2014 г., 14:13
 */

#ifndef VAD_H
#define	VAD_H

#include <string>
#include <vector>
#include <dirent.h>
#include "mfcc.h"
#include "c_svm.h"

class VAD {
public:
    VAD();
//    VAD(const VAD& orig);
    virtual ~VAD();
    
    /**
     * @brief TODO move to global
     * @param path
     * @return 
     */
    static std::vector< std::string > listDir(std::string path);
    
    void initializeMFCC(int windowSize = 512, int overlapSize = 256, int filtersCount = 32, int mfccCount = 16);
    void initializeSVM(int num_features = 16);
    
private:
    SVM*  mSVM;
    MFCC* mMFCC;

};

#endif	/* VAD_H */

