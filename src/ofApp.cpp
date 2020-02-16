#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // Misc setup
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();

    // setup our main Fbo
    ofFboSettings screenFboSettings;
    screenFboSettings.numSamples = 8;
    screenFboSettings.height = ofGetHeight();
    screenFboSettings.width  = ofGetWidth();
    screenFboSettings.internalformat = GL_RGBA32F;
    screenFboSettings.useDepth = true;
    screenFbo.allocate(screenFboSettings);

    // Grid
    grid.resize(80, 80, 50);

    // Stars
    stars.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    screenFbo.begin();
    ofClear(0);

    // grid
    cam.begin();
    grid.draw();
    cam.end();

    // stars
    stars.draw(cam);
    screenFbo.end();

    ofSetColor(255);
    screenFbo.draw(0, 0);

    // Show screen dimensions
    ofSetColor(255, 0, 0);
    char debugText[512];
    sprintf_s(debugText, "WindowSize: %d x %d ScreenSize: %d x %d IsFullscreen: %s", ofGetWidth(), ofGetHeight(), ofGetScreenWidth(), ofGetScreenHeight(), getWindowModeString());
    ofDrawBitmapString(debugText, 5, 18);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
    case OF_KEY_RETURN:
        if (ofGetKeyPressed(OF_KEY_ALT) || ofGetKeyPressed(OF_KEY_LEFT_ALT))
            ofToggleFullscreen();
        break;
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
