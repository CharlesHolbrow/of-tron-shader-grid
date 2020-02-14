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

    // Stars
    starFbo.allocate(1028, 1028, GL_RGBA);
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
    cam.begin();        // CAMERA BEGIN

    // grid
    grid.draw();

    // stars
    ofDisableArbTex();
    starShader.begin();
    ofEnablePointSprites();
    glDepthMask(GL_FALSE); // don't write to the depth mask (check only)
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    starShader.setUniform2f("screenSize", ofGetWidth(), ofGetHeight());
    ofSetColor(255, 0, 0);
    stars.draw(GL_POINTS, 0, starPositions.size());

    ofEnableBlendMode(OF_BLENDMODE_ALPHA); // TODO: double check if this is actually the default blend mode
    glDepthMask(GL_TRUE);
    ofDisablePointSprites();
    starShader.end();
    ofEnableArbTex();


    cam.end();          // CAMERA END
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
