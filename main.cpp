#include <iostream>
#include "vad.h"

int main(int argc, char *argv[])
{
    VAD* vad = new VAD();
    vad->initializeMFCC();
    vad->initializeSVM();
    delete vad;
    printf("just do it\n");
    return 0;
}
