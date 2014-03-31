#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <string>
#include <sndfile.h>

/**
 * @brief The Signal class as sound reader
 */
class Signal
{
public:
    Signal();
    virtual ~Signal();
    
    /**
     * @brief get channel count (mono, stereo, etc.)
     * @return unsigned int
     */
    int getChannelCount();
    
    /**
     * @brief get sample (frame) count
     * @return unsigned int (size_t)
     */
    std::size_t getSampleCount();
    
    /**
     * @brief get sample rate in Hz
     * @return unsigned int
     */
    int getSampleRate();
    
    /**
     * @brief load sound from file
     * @param filename
     * @return bool success
     */
    bool loadFromFile(const std::string& filename );
    
    /**
     * @brief read next value from sound
     * @param value will assign
     * @return unsigned int readed frames
     */
    int readNext(double* value);
    
    /**
     * @brief set seek sound file to 0 offset
     */
    void rewind();
private:
    void clean();
    SNDFILE* mSoundFile;
    SF_INFO* mSoundInfo;
};

#endif // SIGNAL_HPP
