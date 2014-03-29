#include "signal.h"

double Signal::getLittleEndian(int index)
{
    int s = getSamples()[index];
    double t = s / 32768.0;
    return t;
}
