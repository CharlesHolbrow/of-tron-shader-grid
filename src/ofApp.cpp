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
    grid.resize(100, 100, 1);

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
void ofApp::update() {
    if (ofGetKeyPressed('r')) {
        float ramp = 0.0025;
        glm::quat rotation  = glm::angleAxis(ramp, cam.getUpDir());
        cam.rotateAround(rotation, cam.getTarget().getGlobalPosition());
        cam.lookAt(cam.getTarget().getGlobalPosition(), glm::normalize(glm::vec3(0.2, 1, 0)));
    }
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
    if (!resized) {
        vs1.fbo.draw(0, 0, 640, 360);
        vs2.fbo.draw(640, 0, 640, 360);
    } else {
        vs1.fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofLog() << "Resized to: " << w << "x" << h << " - " << getWindowModeString();
    resized = true;
    vs1.cam.setLensOffset({0, 0});
    vs1.resize(w, h);
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
