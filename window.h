#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <math.h>

class Window
{
public:
    static std::vector<double> blackmanHarris(std::size_t size);
    static std::vector<double> hamming(std::size_t size);
    static std::vector<double> hann(std::size_t size);
};

#endif // WINDOW_HPP
