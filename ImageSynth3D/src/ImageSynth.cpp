#include "ImageSynth.h"

ImageSynth::ImageSynth(ofImage image, ofVec3f _pos, float _freqRatio){
    
    freqRatio = _freqRatio;
    
    for (int i = 0; i < filterSize; i++) {
        synth[i] = new ofxSCSynth("simpleSine");
        synth[i]->set("freq", powf(freqRatio, i) + 80);
        synth[i]->set("detune", ofRandom(0.9,1.1));
        synth[i]->create();
        
    }
    
    startTime = ofGetElapsedTimef();
    startFrame = ofGetFrameNum();
    pos = _pos;
    inputImage = synthImage = image;
    
    // modify image
    cv::Mat src_mat, dst_mat;
    src_mat = ofxCv::toCv(inputImage);
    //cv::medianBlur(src_mat, dst_mat, 101);
    cv::GaussianBlur(src_mat, dst_mat, cv::Size(121,121), 120, 120);
    ofxCv::toOf(dst_mat, depthImage);
    depthImage.update();
    
    //synthImage = depthImage;
    synthImage.resize(ofGetWidth(), filterSize);
    synthImage.setImageType(OF_IMAGE_GRAYSCALE);
    
    // init rotation
    rot = ofVec3f(ofRandom(360), ofRandom(360), ofRandom(360));
    rotSpeed = ofVec3f(ofRandom(-baseSpeed, baseSpeed), ofRandom(-baseSpeed, baseSpeed), ofRandom(-baseSpeed, baseSpeed));
        
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    createMesh();
}

void ImageSynth::update(){
    sumLevel = 0;
    scanX = (ofGetFrameNum() - startFrame) % int(synthImage.getWidth());
    for (int i = 0; i < filterSize; i++) {
        synth[filterSize - i - 1]->set("mul", (1.0 - synthImage.getColor(scanX, i).getBrightness() / 255.0) / float(filterSize) * 0.8);
    }
}

void ImageSynth::draw(){
    if (inputImage.getWidth() > 0) {
        ofPushMatrix();
        {
            ofTranslate(pos);
            ofRotateX(rot.x);
            ofRotateY(rot.y);
            ofRotateZ(rot.z);
            rot += rotSpeed;
        
            ofSetColor(255, 210);
            inputImage.getTextureReference().bind();
            mesh.draw();
            inputImage.getTextureReference().unbind();
            
            ofSetColor(255);
            float x = (ofGetFrameNum() - startFrame) % int(inputImage.getWidth()) - inputImage.getWidth()/2.0;
            ofLine(x, -inputImage.getHeight()*1000, x, inputImage.getHeight()*1000);
        }
        ofPopMatrix();
    }
}

ImageSynth::~ImageSynth(){
    for (int i = 0; i < filterSize; i++) {
        synth[i]->free();
    }
}

void ImageSynth::createMesh(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    stepSize = 4;
    ySteps = inputImage.getHeight() / stepSize;
    xSteps = inputImage.getWidth() / stepSize;
    for(int y = 0; y < ySteps; y++) {
        for(int x = 0; x < xSteps; x++) {
            mesh.addVertex(ofVec3f(x * stepSize - inputImage.getWidth()/2.0,
                                   y * stepSize - inputImage.getHeight()/2.0,
                                   3.0 * (depthImage.getColor(x * stepSize, y * stepSize).getBrightness() - 127)));
            mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
        }
    }
    for(int y = 0; y + 1 < ySteps; y++) {
        for(int x = 0; x + 1 < xSteps; x++) {
            int nw = y * xSteps + x;
            int ne = nw + 1;
            int sw = nw + xSteps;
            int se = sw + 1;
            mesh.addIndex(nw);
            mesh.addIndex(ne);
            mesh.addIndex(se);
            mesh.addIndex(nw);
            mesh.addIndex(se);
            mesh.addIndex(sw);
        }
    }
}