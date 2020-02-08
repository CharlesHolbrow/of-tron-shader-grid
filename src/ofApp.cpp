#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableDepthTest();
    shader.load("shadersGL2/shader");

    // ofBook section on working with Meshes
    // https://openframeworks.cc/ofBook/chapters/generativemesh.html#basicsworkingwithofmesh
    // ofMesh docs:
    // https://openframeworks.cc/documentation/3d/ofMesh/
    int xSize = 80;
    int ySize = 80;
    int xVerts = xSize + 1;
    int yVerts = ySize + 1;
    float d = 50;

    vector<ofVec2f> cartesianCoords(xVerts * yVerts, {0, 0});
    {
        int i = 0;
        for (int y = 0; y < yVerts; y++) {
            for (int x = 0; x < xVerts; x++) {
                float height = ofNoise(x * 0.05, y * 0.05);
                height = ofMap(height, 0.75, 1., 0., 400., true);
                mesh.addVertex({x * d, height, y * d});
                cartesianCoords[i++] = ofVec2f(x, y);
            }
        }
    }

    mesh.enableIndices();
    mesh.clearIndices();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            int a = y * xVerts + x;
            int b = a + xVerts + 1;

            mesh.addIndex(a);
            mesh.addIndex(b);
            mesh.addIndex(b-1);
            mesh.addIndex(a);
            mesh.addIndex(a+1);
            mesh.addIndex(b);
        }
    }
    // Give shader access to data
    // https://forum.openframeworks.cc/t/ofvbo-ofvbomesh-generic-attributes/9272/7
    shader.begin();
    int location = shader.getAttributeLocation("cartesianCoords");
    mesh.getVbo().setAttributeData(
                                   location,
                                   &(cartesianCoords[0].x),
                                   2,
                                   yVerts * xVerts,
                                   GL_DYNAMIC_DRAW,
                                   sizeof(ofVec2f));
    shader.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofSetColor(255);

    shader.begin();
    shader.setUniform2f("screenSize", {ofGetWidth(), ofGetHeight()});
    mesh.draw();
    shader.end();

//    mesh.drawFaces();
//    ofSetColor(0, 0, 150);
//    mesh.drawWireframe();

    cam.end();
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
