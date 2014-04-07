#include "window.h"

std::vector<double> Window::blackmanHarris(std::size_t size)
{
    std::vector<double> ret;

    for (std::size_t n = 0; n < size; n++) {
        ret.push_back(
                    0.35875 - 0.48829 * cos(2. * M_PI * n / (size - 1.)) +
                    0.14128 * cos(4. * M_PI * n / (size - 1.)) -
                    0.01168 * cos(6. * M_PI * n / (size - 1.))
        );
    }

    return ret;
}

std::vector<double> Window::hamming(std::size_t size)
{
    std::vector<double> ret;

    for (std::size_t n = 0; n < size; n++) {
        ret.push_back(
                    0.54 - 0.46 * cos( M_PI * 2.0 * n / (size - 1.0) )
        );
    }

    return ret;
}

std::vector<double> Window::hann(std::size_t size)
{
    std::vector<double> ret;

    for (std::size_t n = 0; n < size; n++) {
        ret.push_back(
                    0.5 * (1.0 - cos( M_PI * 2.0 * n / (size - 1.0) ))
        );
    }

    return ret;
}
