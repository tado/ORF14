#include "ofApp.h"
#include "ofxSuperColliderServer.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetWindowPosition(1920, 0);
    
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetLineWidth(1.0);
    //cam.setFarClip(100000);
    //cam.setFov(110);
    //ofSetWindowPosition(1920, 0);
    
    sawNum = 0;
    zscaleRatio = currentZscale = 0.0;
    freqRatio = 1.1;

    ofxSuperColliderServer::init(57110, 96000);
    fx = new ofxSCSynth("fx");
    fx->create();
    sawFx = new ofxSCSynth("col_closefx");
    sawFx->create();
    
    zscale.addListener(this, &ofApp::zscaleChanged);
    fov.addListener(this, &ofApp::fovChanged);
    // gui.setup();
    // gui.add(freqRatio.setup("freqRatio", 1.3, 1.0, 2.0));
    // gui.add(zscale.setup("z-scale", 0.0, 0.0, 10.0));
    // gui.add(fov.setup("fov", 60, 10, 180));
    // gui.loadFromFile("settings.xml");
    
    cam.setFov(100);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->update();
    }
    
    currentZscale += (zscaleRatio - currentZscale) / 1000.0;
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->zscaleRatio = currentZscale;
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
    
    // gui.draw();
    
    ofColor(255);
    ofCircle(mouseX, mouseY, 10);
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
        s->zscale = zscale;
        imageSynths.push_back(s);
        
        freqRatio *= 1.01;
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
    if (key == 'z') {
        SawSynth *saw = new SawSynth(sawNum);
        sawNum++;
        zscaleRatio += 1.0;
        saws.push_back(saw);
    }
    if (key == 'k') {
        for (int j = 0; j < imageSynths.size(); j++) {
            for (int i = 0; i < imageSynths[j]->filterSize; i++) {
                imageSynths[j]->synth[i]->free();
            }
        }
        for (int i = 0; i < saws.size(); i++) {
            saws[i]->synth->free();
        }
        imageSynths.clear();
    }
}

void ofApp::zscaleChanged(float & zscale){
    for (int i = 0; i < imageSynths.size(); i++) {
        imageSynths[i]->zscale = zscale;
    }
}

void ofApp::fovChanged(float & fov){
    cam.setFov(fov);
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

