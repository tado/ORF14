#include "ofApp.h"
#include "ofxSuperColliderServer.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetLineWidth(1.0);
    cam.setFarClip(100000);
    cam.setFov(110);

    //ofxSuperColliderServer::init();
    fx = new ofxSCSynth("fx");
    fx->create();
    
    gui.setup();
    gui.add(freqRatio.setup("freqRatio", 1.2, 1.0, 2.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->draw();
    }
    cam.end();
    ofDisableDepthTest();
    
    gui.draw();
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    vector<ofImage> draggedImages;
    if( dragInfo.files.size() > 0 ){
        // get image data
        draggedImages.assign( dragInfo.files.size(), ofImage() );
        for(unsigned int k = 0; k < dragInfo.files.size(); k++){
            draggedImages[k].loadImage(dragInfo.files[k]);
        }
        
        float size = 500;
        ofVec3f pos = ofVec3f(ofRandom(-size, size), ofRandom(-size, size), ofRandom(-size, size));
        ImageSynth *s = new ImageSynth(draggedImages[0], pos, freqRatio);
        imageSynths.push_back(s);        
    }
}

ofApp::~ofApp(){
    fx->free();
    for (int i = 0; i < imageSynths.size(); i++) {
        delete imageSynths[i];
    }
    imageSynths.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        if (imageSynths.size()>0) {
            for (int i = 0; i < imageSynths[0]->filterSize; i++) {
                imageSynths[0]->synth[i]->free();
            }
            imageSynths.pop_front();
        }
    }
    if (key == 's') {
        if (imageSynths.size()>0) {
            for (int i = 0; i < imageSynths[imageSynths.size()-1]->filterSize; i++) {
                imageSynths[imageSynths.size()-1]->synth[i]->free();
            }
            imageSynths.pop_back();
        }
    }
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

