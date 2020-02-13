#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Misc setup
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableDepthTest();

    // Grid
    grid.resize(80, 80, 50);

    // Everything else
    starFbo.allocate(1028, 1028, GL_RGBA);
    starShader.load("shadersGL3/stargen");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofSetColor(255);
    grid.draw();
    cam.end();

    starFbo.begin();    // FBO begin
    starShader.begin(); // Shader begin
    ofClear(0, 0, 0, 0);
    starShader.setUniform2f("screenSize", {1028, 1028});
    ofDrawRectangle(0, 0, 1028, 1028);

    starShader.end();   // Shader end
    starFbo.end();
    starFbo.draw(0, 0, 512, 512);
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
