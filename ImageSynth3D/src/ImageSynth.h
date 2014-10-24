#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"

class ImageSynth {
public:
    ImageSynth(ofImage image, ofVec3f pos);
    ~ImageSynth();
    void update();
    void draw();
    
    static const int filterSize = 40;
    ofxSCSynth *synth[filterSize];
    int scanX;
    int startFrame;
    ofImage inputImage, synthImage;
    ofVec3f pos;
    float startTime;
    ofVec3f rot;
    ofVec3f rotSpeed;
    
    const float baseSpeed = 0.05;
};