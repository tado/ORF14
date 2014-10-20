#include "ofApp.h"
//#include "ofxSuperColliderServer.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    //ofxSuperColliderServer::init();
    
    fx = new ofxSCSynth("fx");
    fx->create();
    
    for (int i = 0; i < filterSize; i++) {
        synth[i] = new ofxSCSynth("simpleSine");
        synth[i]->set("freq", powf(1.2, i) + 50);
        synth[i]->set("detune", ofRandom(0.9,1.1));
        synth[i]->create();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    scanX = (ofGetFrameNum() - startFrame) % ofGetWidth();
    for (int i = 0; i < filterSize; i++) {
        synth[filterSize - i - 1]->set("mul", (1.0 - synthImage.getColor(scanX, i).getBrightness() / 255.0) / float(filterSize) * 2.0);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    if (inputImage.getWidth() > 0) {
        inputImage.draw(0, 0, ofGetWidth(), ofGetHeight());
        
        ofSetColor(255, 0, 0);
        ofLine(scanX, 0, scanX, ofGetHeight());
    }
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    vector<ofImage> draggedImages;
    if( dragInfo.files.size() > 0 ){
        
        startFrame = ofGetFrameNum();
        
        // get image data
        draggedImages.assign( dragInfo.files.size(), ofImage() );
        for(unsigned int k = 0; k < dragInfo.files.size(); k++){
            draggedImages[k].loadImage(dragInfo.files[k]);
        }
        draggedImages[0].resize(ofGetWidth(), ofGetHeight());
        inputImage = synthImage = draggedImages[0];
        
        // modify image
        synthImage.resize(ofGetWidth(), filterSize);
        //cv::Mat src_mat, dst_mat;
        //src_mat = ofxCv::toCv(inputImage);
        //copyGray(src_mat, dst_mat);
        //cv::medianBlur(src_mat, dst_mat, 11);
        //ofxCv::toOf(dst_mat, inputImage);
        synthImage.setImageType(OF_IMAGE_GRAYSCALE);
        synthImage.update();
    }
}

ofApp::~ofApp(){
    fx->free();
    for (int i = 0; i < filterSize; i++) {
        synth[i]->free();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

