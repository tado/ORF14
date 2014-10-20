#include "ofApp.h"
#include "ofxSuperColliderServer.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofxSuperColliderServer::init();
    
    fx = new ofxSCSynth("fx");
    fx->create();
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->draw();
    }
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    vector<ofImage> draggedImages;
    if( dragInfo.files.size() > 0 ){
        // get image data
        draggedImages.assign( dragInfo.files.size(), ofImage() );
        for(unsigned int k = 0; k < dragInfo.files.size(); k++){
            draggedImages[k].loadImage(dragInfo.files[k]);
        }
        
        ImageSynth *s = new ImageSynth(draggedImages[0], ofVec2f(mouseX, mouseY));
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

