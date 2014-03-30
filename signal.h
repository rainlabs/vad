#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <string>
#include <sndfile.h>
//#include <SFML/Audio/SoundBuffer.hpp>
//#include <SFML/Audio/Sound.hpp>

/**
 * @brief The Signal class as sound reader
 */
class Signal
{
public:
    Signal();
    virtual ~Signal();
    
    int getChannelCount();
    std::size_t getSampleCount();
    int getSampleRate();
    
    bool loadFromFile(const std::string& filename );
    int readNext(double* value);
    void rewind();
private:
    void clean();
    SNDFILE* mSoundFile;
    SF_INFO* mSoundInfo;
};

#endif // SIGNAL_HPP
