#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Misc setup
    ofBackground(0);
    ofSetFrameRate(60);
//    ofEnableSmoothing();
//    ofEnableAntiAliasing();
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
    starShader.load("shadersGL3/stargen");
    // randomly add a point on a sphere
    int   num = 500;
    for(int i = 0; i<num; i++ ) {

        float theta1 = ofRandom(0, TWO_PI);
        float theta2 = ofRandom(0, TWO_PI);

        ofVec3f p;
        p.x = cos( theta1 ) * cos( theta2 );
        p.y = sin( theta1 );
        p.z = cos( theta1 ) * sin( theta2 );
        p *= ofRandom(2000, 10000); // radius
        starPositions.push_back(p);
    }
    int count = starPositions.size();
    stars.setVertexData(&starPositions[0], count, GL_STATIC_DRAW);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    screenFbo.begin();
    ofClear(0);


    // grid
    cam.begin();
    grid.draw();
    cam.end();

    // stars
    starShader.begin();
    ofEnablePointSprites();
    glDepthMask(GL_FALSE); // don't write to the depth mask (check only)
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // Annoyingly, when a non-default VBO is active, shaders are not passed
    // accurate camera matrices, so I am manually passing in camera matrices.
    // Note that this means that we also have to manually flip the y-axis, which
    // openFrameworks usually manages for us. This is necessary because OF and
    // OpenGL use different coordinate conventions.
    glm::mat4x4 flipY;
    flipY[1][1] = -1.0;
    starShader.setUniform2f("screenSize", ofGetWidth(), ofGetHeight());
    starShader.setUniformMatrix4f("mv", flipY * cam.getModelViewMatrix());
    starShader.setUniformMatrix4f("p", cam.getProjectionMatrix());
    ofSetColor(255, 0, 0);
    stars.draw(GL_POINTS, 0, starPositions.size());

    ofEnableBlendMode(OF_BLENDMODE_ALPHA); // TODO: double check if this is actually the default blend mode
    glDepthMask(GL_TRUE);
    ofDisablePointSprites();
    starShader.end();


    screenFbo.end();
    screenFbo.draw(0, 0);
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
