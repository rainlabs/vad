#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
//#include <SFML/Audio/Sound.hpp>

/**
 * @brief The Signal class as sound buffer
 */
class Signal : public sf::SoundBuffer
{
public:
    Signal() : SoundBuffer() {}
    Signal(const SoundBuffer &copy) : SoundBuffer(copy) {}
    ~Signal() {}

    double getLittleEndian(int index);
};

#endif // SIGNAL_HPP
