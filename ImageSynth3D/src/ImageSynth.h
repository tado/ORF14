#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"
#include "ofxCv.h"

class ImageSynth {
public:
    ImageSynth(ofImage image, ofVec3f pos);
    ~ImageSynth();
    void update();
    void draw();
    void createMesh();
    
    static const int filterSize = 50;
    ofxSCSynth *synth[filterSize];
    int scanX;
    int startFrame;
    ofImage inputImage, synthImage, depthImage;
    ofVec3f pos;
    float startTime;
    ofVec3f rot;
    ofVec3f rotSpeed;
    float sumLevel;
    const float baseSpeed = 0.05;
    
    ofMesh mesh;
    int stepSize, xSteps, ySteps;
};