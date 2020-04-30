#ifndef SOUNDS_H
#define SOUNDS_H

#include "ofMain.h"
#include "ofApp.h"

class Sounds
{
public:

    Sounds(){}

    void setup(){
        soundSettings.setApi( ofSoundDevice::PULSE );
        soundSettings.setOutListener(ofGetAppPtr());
        soundSettings.numOutputChannels = 2;
        soundSettings.numInputChannels = 0;
        ofSoundStreamSetup(soundSettings);
    }

    ofSoundStreamSettings soundSettings;

private:
};

#endif // SOUNDS_H
