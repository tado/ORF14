#include "ImageSynth.h"

ImageSynth::ImageSynth(ofImage image, ofVec3f _pos){
    for (int i = 0; i < filterSize; i++) {
        synth[i] = new ofxSCSynth("simpleSine");
        synth[i]->set("freq", powf(1.4, i) + 80);
        synth[i]->set("detune", ofRandom(0.9,1.1));
        synth[i]->create();
        
    }
    
    startTime = ofGetElapsedTimef();
    startFrame = ofGetFrameNum();
    pos = _pos;
    inputImage = synthImage = image;
    
    // modify image
    synthImage.resize(ofGetWidth(), filterSize);
    synthImage.setImageType(OF_IMAGE_GRAYSCALE);
    
    // init rotation
    rot = ofVec3f(ofRandom(360), ofRandom(360), ofRandom(360));
    rotSpeed = ofVec3f(ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1), ofRandom(-0.1, 0.1));
}

void ImageSynth::update(){
    scanX = (ofGetFrameNum() - startFrame) % int(synthImage.getWidth());
    //if (ofGetFrameNum() % 4 == 0) {
    for (int i = 0; i < filterSize; i++) {
        synth[filterSize - i - 1]->set("mul", (1.0 - synthImage.getColor(scanX, i).getBrightness() / 255.0) / float(filterSize));
    }
    //}
}

void ImageSynth::draw(){
    if (inputImage.getWidth() > 0) {
        ofPushMatrix();
        ofTranslate(pos);
        /*
        ofRotateX(ofGetElapsedTimef() - startTime);
        ofRotateY((ofGetElapsedTimef() - startTime) * 1.2);
        ofRotateZ((ofGetElapsedTimef() - startTime) * 1.3);
         */
        ofRotateX(rot.x);
        ofRotateY(rot.y);
        ofRotateZ(rot.z);
        rot += rotSpeed;
        
        ofSetColor(255, 180);
        inputImage.draw(-inputImage.getWidth()/2.0, -inputImage.getHeight()/2.0);
        ofSetColor(255);
        float x = (ofGetFrameNum() - startFrame) % int(inputImage.getWidth()) - inputImage.getWidth()/2;;
        ofLine(x, -inputImage.getHeight()/2.0, x, inputImage.getHeight()/2.0);
        ofPopMatrix();
    }
}

ImageSynth::~ImageSynth(){
    for (int i = 0; i < filterSize; i++) {
        synth[i]->free();
    }
}