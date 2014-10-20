#include "ImageSynth.h"

ImageSynth::ImageSynth(ofImage image, ofVec3f _pos){
    for (int i = 0; i < filterSize; i++) {
        synth[i] = new ofxSCSynth("simpleSine");
        synth[i]->set("freq", powf(2.0, i) + 100);
        synth[i]->set("detune", ofRandom(0.9,1.1));
        synth[i]->create();
        startTime = ofGetElapsedTimef();
    }
    
    pos = _pos;
    inputImage = synthImage = image;
        
    // modify image
    //inputImage.resize(ofGetWidth(), ofGetHeight());
    synthImage.resize(ofGetWidth(), filterSize);
    synthImage.setImageType(OF_IMAGE_GRAYSCALE);
    //synthImage.update();
}

void ImageSynth::update(){
    scanX = (ofGetFrameNum() - startFrame) % ofGetWidth();
    if (ofGetFrameNum() % 4 == 0) {
        for (int i = 0; i < filterSize; i++) {
            synth[filterSize - i - 1]->set("mul", (1.0 - synthImage.getColor(scanX, i).getBrightness() / 255.0) / float(filterSize) / 3.0);
        }
    }
}

void ImageSynth::draw(){
    ofSetColor(255);
    if (inputImage.getWidth() > 0) {
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateX(ofGetElapsedTimef() - startTime);
        ofRotateY((ofGetElapsedTimef() - startTime) * 1.2);
        ofRotateZ((ofGetElapsedTimef() - startTime) * 1.3);
        inputImage.draw(-inputImage.width / 2.0, -inputImage.height/2.0);
        ofPopMatrix();
    }
}

ImageSynth::~ImageSynth(){
    for (int i = 0; i < filterSize; i++) {
        synth[i]->free();
    }
}