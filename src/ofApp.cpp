#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // Misc setup
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();

    int w = 640;
    int h = 360;
    // this sets fbo
    vs1.resize(w, h);
    vs2.resize(w, h);

    // Grid
    grid.resize(80, 80, 1);

    // Stars
    stars.setup();

    // Camera Stuff
    cam.setNearClip(1);
    cam.setFarClip(1000);
    cam.setDistance(13);

    vs1.setup(cam);
    vs1.cam.setLensOffset({-1, 0});
    vs2.setup(cam);
    vs2.cam.setLensOffset({1, 0});
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw() {
    // The call to cam.begin/end() implicitly enables easycam mouse controls
    cam.begin();
    cam.end();

    vs1.clear();
    vs1.begin();
    grid.draw();
    stars.draw(vs1.cam, vs1.fbo.getWidth(), vs1.fbo.getHeight());
    vs1.end();

    vs2.clear();
    vs2.begin();
    grid.draw();
    stars.draw(vs2.cam, vs2.fbo.getWidth(), vs2.fbo.getHeight());
    vs2.end();

    ofSetColor(255);
    vs1.fbo.draw(0, 0, 640, 360);
    vs2.fbo.draw(640, 0, 640, 360);

    // Show screen dimensions
//    ofSetColor(255, 0, 0);
//    char debugText[512];
//    sprintf(debugText, "WindowSize: %d x %d ScreenSize: %d x %d Window: %s FOV: %5.2f aspectRatio: %5.2f"
//        , ofGetWidth()
//        , ofGetHeight()
//        , ofGetScreenWidth()
//        , ofGetScreenHeight()
//        , getWindowModeString()
//        , cam.getFov()
//        , cam.getAspectRatio());
//    ofDrawBitmapString(debugText, 5, 18);
//    auto pos = cam.getGlobalPosition();
//    sprintf(debugText, "CAMERA Pos: %4.2f %4.2f %4.2f Near/Far: % 6.3f/% 6.3f Distance: % 6.3f ", pos.x, pos.y, pos.z, cam.getNearClip(), cam.getFarClip(), cam.getDistance());
//    ofDrawBitmapString(debugText, 5, 36);
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
