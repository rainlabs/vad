#include "signal.h"

Signal::Signal() {
    mSoundFile = nullptr;
    mSoundInfo = nullptr;
}

Signal::~Signal() {
    clean();
}

bool Signal::loadFromFile(const std::string& filename) {
    clean();
    mSoundInfo = new SF_INFO;
    mSoundInfo->format = 0;
    
    mSoundFile = sf_open(filename.data(), SFM_READ, mSoundInfo);
    
    return (mSoundFile != nullptr);
}

int Signal::getChannelCount() {
    return mSoundInfo->channels;
}

std::size_t Signal::getSampleCount() {
    return mSoundInfo->frames;
}

int Signal::getSampleRate() {
    return mSoundInfo->samplerate;
}

void Signal::clean() {
    if(mSoundFile != nullptr)
        delete mSoundFile;
    
    if(mSoundInfo != nullptr)
        delete mSoundInfo;
}

int Signal::readNext(double* value) {
    return sf_read_double(mSoundFile, value, 1);
}

void Signal::rewind() {
    sf_seek(mSoundFile, 0, SEEK_SET);
}