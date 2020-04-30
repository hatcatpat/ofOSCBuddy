#ifndef OSC_H
#define OSC_H

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofApp.h"


class OSC
{
public:

    ofEvent<ofxOscMessage> instant_event;
    ofEvent<ofxOscMessage> timed_event;

    OSC(){}

    void setup(int in_port, int out_port, int _sample_rate, int _buffer_size, float _dur_seconds=0.5){
        osc_receiver.setup(in_port);
        sample_rate = _sample_rate; buffer_size = _buffer_size; dur_seconds = _dur_seconds;
        durSecToSamp();

        osc_sender.setup("127.0.0.1", out_port);
        init_msg.setAddress("/init");
        bang_msg.setAddress("/bang");

        osc_sender.sendMessage(init_msg);
    }

    void update(){

        while (osc_receiver.hasWaitingMessages()){
            ofxOscMessage msg;
            osc_receiver.getNextMessage(msg);

            if (msg.getNumArgs() == 0){
                processInstantOsc(msg);
            } else {
                int timeTag = (msg.getArgAsInt(0))%mod;
                message_seq[timeTag].push_back(msg);
            }
        }

    }

    void process(){

        if (t == 0){

            osc_sender.sendMessage(bang_msg);

            std::vector<ofxOscMessage> fixed_message_seq = message_seq[T];

            for (ofxOscMessage msg : fixed_message_seq)
                processTimedOsc(msg);

            message_seq[T].clear();
            T++;
            T %= mod;
        }

        t++;
        t %= dur_samples;

    }

    void processTimedOsc(ofxOscMessage msg){
        ofNotifyEvent(timed_event, msg);
    }

    void processInstantOsc(ofxOscMessage msg){
        ofNotifyEvent(instant_event, msg);
    }

    void setDur(float _dur_sec){
        dur_seconds = _dur_sec;
        durSecToSamp();
    }

    void draw(){

        for (int i=0; i < mod; i++){
            if (i == T){
                ofSetColor(255,0,0);
            } else {
                ofSetColor(255);
            }
            ofDrawBitmapString(message_seq[i], 32, 32+i*(ofGetHeight()-32*2)/mod );
        }

    }

    void durSecToSamp(){ dur_samples = dur_seconds * sample_rate / buffer_size; }

private:

    ofxOscReceiver osc_receiver;
    ofxOscSender osc_sender;

    ofxOscMessage init_msg;
    ofxOscMessage bang_msg;

    float dur_seconds = 1.0;
    int dur_samples = 44100;
    int sample_rate = 44100;
    int buffer_size = 512;

    const static int START_MOD = 16;
    int mod = START_MOD;
    std::vector<ofxOscMessage> message_seq[START_MOD*8];

    int t = 0;
    int T = 0;

};

#endif // OSC_H
