#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // Misc setup
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();

    // this sets fbo
    windowResized(ofGetWidth(), ofGetHeight());

    // Grid
    grid.resize(80, 80, 1);

    // Stars
    stars.setup();

    // Camera Stuff
    cam.setNearClip(1);
    cam.setFarClip(1000);
    cam.setDistance(13);
    
    c1.setNearClip(1);
    c1.setFarClip(1000);
    c1.setParent(cam);
    c1.setFov(60);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    // The call to cam.begin/end() implicitly enables easycam mouse controls
    cam.begin();
    cam.end();

    screenFbo.begin();
    ofClear(0);

    // grid
    c1.begin();
    grid.draw();
    c1.end();

    // stars
    stars.draw(cam);
    screenFbo.end();

    ofSetColor(255);
    screenFbo.draw(0, 0);

    // Show screen dimensions
    ofSetColor(255, 0, 0);
    char debugText[512];
    sprintf_s(debugText, "WindowSize: %d x %d ScreenSize: %d x %d Window: %s FOV: %5.2f aspectRatio: %5.2f"
        , ofGetWidth()
        , ofGetHeight()
        , ofGetScreenWidth()
        , ofGetScreenHeight()
        , getWindowModeString()
        , cam.getFov()
        , cam.getAspectRatio());
    ofDrawBitmapString(debugText, 5, 18);
    auto pos = cam.getGlobalPosition();
    sprintf_s(debugText, "CAMERA Pos: %4.2f %4.2f %4.2f Near/Far: % 6.3f/% 6.3f Distance: % 6.3f ", pos.x, pos.y, pos.z, cam.getNearClip(), cam.getFarClip(), cam.getDistance());
    ofDrawBitmapString(debugText, 5, 36);
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
    // setup our main Fbo
    ofFboSettings screenFboSettings;
    screenFboSettings.numSamples = 8;
    screenFboSettings.height = ofGetHeight();
    screenFboSettings.width = ofGetWidth();
    screenFboSettings.internalformat = GL_RGBA32F;
    screenFboSettings.useDepth = true;
    screenFbo.allocate(screenFboSettings);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
