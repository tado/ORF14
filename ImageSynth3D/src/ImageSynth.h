#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"

class ImageSynth {
public:
    ImageSynth(ofImage image, ofVec2f pos);
    ~ImageSynth();
    void update();
    void draw();
    
    static const int filterSize = 100;
    ofxSCSynth *synth[filterSize];
    int scanX;
    int startFrame;
    ofImage inputImage, synthImage;
    ofVec2f pos;
};