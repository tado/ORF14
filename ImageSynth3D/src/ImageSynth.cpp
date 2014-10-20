#include "ImageSynth.h"

ImageSynth::ImageSynth(ofImage image, ofVec2f _pos){
    for (int i = 0; i < filterSize; i++) {
        synth[i] = new ofxSCSynth("simpleSine");
        synth[i]->set("freq", powf(1.1, i) + 100);
        synth[i]->set("detune", ofRandom(0.9,1.1));
        synth[i]->create();
    }
    
    pos = _pos;
    inputImage = synthImage = image;
        
    // modify image
    inputImage.resize(ofGetWidth(), ofGetHeight());
    synthImage.resize(ofGetWidth(), filterSize);

    //cv::Mat src_mat, dst_mat;
    //src_mat = ofxCv::toCv(inputImage);
    //copyGray(src_mat, dst_mat);
    //cv::medianBlur(src_mat, dst_mat, 11);
    //ofxCv::toOf(dst_mat, inputImage);
    
    synthImage.setImageType(OF_IMAGE_GRAYSCALE);
    synthImage.update();
}

void ImageSynth::update(){
    scanX = (ofGetFrameNum() - startFrame) % ofGetWidth();
    for (int i = 0; i < filterSize; i++) {
        synth[filterSize - i - 1]->set("mul", (1.0 - synthImage.getColor(scanX, i).getBrightness() / 255.0) / float(filterSize) * 2.0);
    }
}

void ImageSynth::draw(){
    ofSetColor(255);
    if (inputImage.getWidth() > 0) {
        inputImage.draw(pos, ofGetWidth()/4, ofGetHeight()/4);
        
        //ofSetColor(255, 0, 0);
        //ofLine(scanX, 0, scanX, ofGetHeight());
    }
}

ImageSynth::~ImageSynth(){
    for (int i = 0; i < filterSize; i++) {
        synth[i]->free();
    }
}