# OpenFrameworksOSCBuddy
A small script to help with well-timed OSC input, as well as a simple audio-settings class.

Usage:
In ofApp.h
```cpp
OSC osc;
Sounds sounds;
```
In ofApp.cpp
```cpp

void ofApp::setup(){
  sounds.setup();
  osc.setup(12000, 5005, sounds.soundSettings.sampleRate, sounds.soundSettings.bufferSize, 0.5);
  // arguments are IN_PORT, OUT_PORT, SAMPLERATE, BUFFERSIZE, DURATION

  ofAddListener(osc.timed_event, this, &ofApp::process_timed);
  ofAddListener(osc.instant_event, this, &ofApp::process_instant);
}

void ofApp::process_timed(ofxOscMessage & msg){
    // DO STUFF WITH INCOMING OSC MESSAGES THAT REQUIRE GOOD TIMING
}
void ofApp::process_instant(ofxOscMessage & msg){
    // DO STUFF WITH INCOMING OSC THAT DOESN'T REQUIRE GOOD TIMING
}

void ofApp::audioOut(ofSoundBuffer &outBuffer){
    osc.process();
}
void ofApp::update(){
    osc.update();
}
void ofApp::draw(){
    osc.draw(); // USE DRAW FOR DEBUGGING
}

```
