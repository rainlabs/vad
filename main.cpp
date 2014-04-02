#include <iostream>
#include "vad.h"
#include "tests/test_helper.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    MFCC* mfcc = new MFCC();
    int i;
    int duration = 30;
    float hzInterval = 1000. / duration;
    std::string filename = "out";
    mfcc->load(argv[1]);
    auto out = mfcc->extract();
    
    std::vector<float> x, y;
    
    for(i = 0; i < out.size(); i++)
        x.push_back( i*duration / 1000. );
    for(i = 0; i < out.back().size(); i++)
        y.push_back( i*hzInterval );
    
    TestHelper::saveMatrix(out, x, y, filename);
    TestHelper::plotMatrix(filename);
    
    return 0;
}
