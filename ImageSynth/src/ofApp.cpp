#include "ofApp.h"
#include "ofxSuperColliderServer.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofxSuperColliderServer::init();
    
    
    fx = new ofxSCSynth("fx");
    fx->create();
    
    for (int i = 0; i < filterSize; i++) {
        synth[i] = new ofxSCSynth("simpleSine");
        synth[i]->set("detune", ofRandom(0.9,1.15));
        synth[i]->create();
    }
    
    ratio.addListener(this, &ofApp::ratioChanged);
    freqOffset.addListener(this, &ofApp::freqOffsetChanged);

    gui.setup();
    gui.add(autoScan.setup("auto scan", true));
    gui.add(useCam.setup("use camera", false));
    gui.add(scanSpeed.setup("scan speed", 1.0, 0.0, 5.0));
    gui.add(ratio.setup("freq ratio", 1.15, 1.0, 1.3));
    gui.add(freqOffset.setup("freq offset", 20, 0, 400));
    gui.add(amp.setup("amplitude", 0.01, 0.0, 0.1));
    gui.loadFromFile("settings.xml");
    
    
    for (int i = 0; i < filterSize; i++) {
        synth[i]->set("freq", powf(ratio, i) + freqOffset);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if (autoScan) {
        scanX += scanSpeed;
        if (scanX > ofGetWidth()) {
            scanX = 0;
        }
    } else {
        if (mouseX > 0 && mouseX < ofGetWidth()) {
            scanX = mouseX;
        }
    }
    for (int i = 0; i < filterSize; i++) {
        synth[filterSize - i - 1]->set("mul", (1.0 - synthImage.getColor(scanX, i).getBrightness() / 255.0) * amp);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (inputImage.getWidth() > 0) {
        ofSetColor(255);
        inputImage.draw(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(127);
        ofSetLineWidth(3.0);
        ofLine(scanX, 0, scanX, ofGetHeight());
        ofSetLineWidth(1.0);
    }
    
    ofSetColor(255);
    gui.draw();
}

void ofApp::ratioChanged(float & ratio){
    for (int i = 0; i < filterSize; i++) {
        synth[i]->set("freq", powf(ratio, i) + freqOffset);
    }
}

void ofApp::freqOffsetChanged(float & freqOffset){
    for (int i = 0; i < filterSize; i++) {
        synth[i]->set("freq", powf(ratio, i) + freqOffset);
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
        
        //reset scanX
        scanX = 0;
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

