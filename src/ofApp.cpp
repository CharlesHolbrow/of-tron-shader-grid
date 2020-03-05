#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // Misc setup
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();

    // prepare fbo
    vs0.resize(ofGetWidth(), ofGetHeight());

    // stuff for two screen mode
    int w = 640;
    int h = 360;
    // this sets fbo
    vs1.resize(w, h);
    vs2.resize(w, h);

    // Grid
    grid.resize(60, 60, 1);

    // Stars
    stars.setup();

    // Logo
    logo.setup();

    // Camera Stuff
    cam.setNearClip(1);
    cam.setFarClip(1000);
    cam.setDistance(13);
    cam.setRelativeYAxis(false);

    vs0.setup(cam);
    vs1.setup(cam);
    vs1.cam.setLensOffset({-1, 0});
    vs2.setup(cam);
    vs2.cam.setLensOffset({1, 0});

    // lerp stuff
    lerpZoom.duration = 0.5;
    orbitSpeed.duration = 3;
    orbitAngle.duration = 10;

    // OSC
    receiver.setup(12340);
}

//--------------------------------------------------------------
void ofApp::update() {
    // Calculate the frame's delta
    uint64_t currentFrameMicroseconds = ofGetElapsedTimeMicros();
    uint64_t currentDeltaMicroseconds = currentFrameMicroseconds - lastFrameMicroseconds;
    lastFrameMicroseconds = currentFrameMicroseconds;
    double deltaSeconds = currentDeltaMicroseconds * 0.000001;

    // bump our LFOs
    v1.advance(deltaSeconds);
    t1.advance(deltaSeconds);
    saw1.advance(deltaSeconds);

    if (ofGetKeyPressed('r')) {
        float ramp = 0.0025;
        glm::quat rotation  = glm::angleAxis(ramp, cam.getUpDir());
        cam.rotateAround(rotation, cam.getTarget().getGlobalPosition());
        cam.lookAt(cam.getTarget().getGlobalPosition(), glm::normalize(glm::vec3(0.2, 1, 0)));
    }

    // Logo
    logo.update(deltaSeconds);

    // OSC
    ofxOscMessage msg;
    while (receiver.getNextMessage(msg)) handleOscMessage(msg);

    cam.setDistance(lerpZoom.get());

    // Orbit
    orbitRadians += float(orbitSpeed) * deltaSeconds;
    float distance = glm::length(cam.getGlobalPosition() - cam.getTarget().getGlobalPosition());
    glm::vec3 pos = glm::rotate(glm::vec3(0, 0, distance), orbitRadians, upAxis);
    upAxis = glm::rotate(glm::vec3(0, 1, 0), (float)orbitAngle.get(), glm::vec3(1, 0, 0));
    cam.setPosition(pos);
    cam.lookAt(logo.node, upAxis);
}

//--------------------------------------------------------------
void ofApp::draw() {
    // The call to cam.begin/end() implicitly enables easycam mouse controls
    cam.begin();
    cam.end();

    if (twoScreenMode) {
        vs1.clear();
        vs1.begin();
        grid.draw();
        logo.draw();
        stars.draw(vs1.cam, vs1.fbo.getWidth(), vs1.fbo.getHeight());
        vs1.end();

        vs2.clear();
        vs2.begin();
        grid.draw();
        logo.draw();
        stars.draw(vs2.cam, vs2.fbo.getWidth(), vs2.fbo.getHeight());
        vs2.end();

        // draw the two screens
        vs1.fbo.draw(0, 0, 640, 360);
        vs2.fbo.draw(640, 0, 640, 360);
    } else {
        vs0.clear();
        vs0.begin();
        grid.draw();
        stars.draw(vs0.cam, vs0.fbo.getWidth(), vs0.fbo.getHeight());
        logo.draw();
        vs0.end();
        // draw one screen
        ofSetColor(255);
        vs0.fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    }

    ofDisableDepthTest();
    ofSetColor((double)saw1 * 255, 0, 0);
    ofDrawCircle(20, 20, 10);
    ofSetColor(255);
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofLog() << "Resized to: " << w << "x" << h << " - " << getWindowModeString();
    resized = true;
    vs0.resize(w, h);
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

void ofApp::handleOscMessage(const ofxOscMessage &msg) {
    auto addr = msg.getAddress();

    if (addr == "/1/fader1") {
        // zoom
        lerpZoom.setTarget(ofMap(msg.getArgAsFloat(0), 0, 1, 80, 1));
    } else if (addr == "/1/fader5") {
        // bump orbit
        float v = msg.getArgAsFloat(0);
        float target = ofMap(v, 0, 1, -3, 3);
        orbitSpeed.jumpTo(target);
        restingOrbitSpeed = (target >= 0) ? abs(restingOrbitSpeed) : abs(restingOrbitSpeed) * -1;
        orbitSpeed.setTarget(restingOrbitSpeed);
    } else if (addr == "/1/fader3") {
        // resting orbit speed
        float v = ofMap(msg.getArgAsFloat(0), 0, 1, 0, 0.3);
        if (orbitSpeed >= 0) restingOrbitSpeed = v;
        else restingOrbitSpeed = -v;
        orbitSpeed.setTarget(restingOrbitSpeed);
    } else if (addr == "/1/fader4") {
        // orbit angle
        float v = msg.getArgAsFloat(0);
        v = ofMap(v, 0, 1, 0, PI/2);
        orbitAngle.setTarget(v);
    } else if (addr == "/1/toggle1") {
        logo.enabled = msg.getArgAsInt32(0);
    } else if (addr == "/1/toggle2") {
        stars.enabled = msg.getArgAsInt32(0);
    } else if (addr == "/1/toggle3") {
        grid.enabled = msg.getArgAsInt32(0);
    } else if (addr == "/1/toggle4") {
    } else {
        ofLog() << "Unhandled:" << addr;
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
