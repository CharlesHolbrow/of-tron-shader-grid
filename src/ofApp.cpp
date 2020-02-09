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

    vector<ofVec2f> cartesianCoords(xSize * ySize * 6, {0, 0});
    vector<ofVec3f> vertices(xVerts * yVerts);
    {
        int i = 0;
        for (int y = 0; y < yVerts; y++) {
            for (int x = 0; x < xVerts; x++) {
                float height = ofNoise(x * 0.05, y * 0.05);
                height = ofMap(height, 0.75, 1., 0., 400., true);
                ofVec3f vertex(x*d, height, y*d);
                vertices[i++] = vertex;
            }
        }
    }

    mesh.enableNormals();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    int i = 0;
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            int a = y * xVerts + x;
            int b = a + xVerts + 1;

            ofVec3f v0 = vertices[a];
            ofVec3f v1 = vertices[b];
            ofVec3f v2 = vertices[b-1];
            mesh.addVertex(v0);
            mesh.addVertex(v1);
            mesh.addVertex(v2);
            cartesianCoords[i++] = {v0.x / d, v0.z / d};
            cartesianCoords[i++] = {v1.x / d, v1.z / d};
            cartesianCoords[i++] = {v2.x / d, v2.z / d};

            // Simple normals https://forum.openframeworks.cc/t/solved-how-to-properly-calculate-normals-of-the-box/25487
            // normal for t1
            ofVec3f U = v1 - v0;
            ofVec3f V = v2 - v0;
            float xn = (U.y * V.z) - (U.z * V.y);
            float yn = (U.z * V.x) - (U.x * V.z);
            float zn = (U.x * V.y) - (U.y * V.x);
            ofVec3f normal = ofVec3f(xn,yn,zn);
            normal.normalize();
            mesh.addNormal(normal);
            mesh.addNormal(normal);
            mesh.addNormal(normal);

            v0 = vertices[a];
            v1 = vertices[a+1];
            v2 = vertices[b];
            mesh.addVertex(v0);
            mesh.addVertex(v1);
            mesh.addVertex(v2);
            cartesianCoords[i++] = {v0.x / d, v0.z / d};
            cartesianCoords[i++] = {v1.x / d, v1.z / d};
            cartesianCoords[i++] = {v2.x / d, v2.z / d};

            // normal for t2
            U = v1 - v0;
            V = v2 - v0;
            xn = (U.y * V.z) - (U.z * V.y);
            yn = (U.z * V.x) - (U.x * V.z);
            zn = (U.x * V.y) - (U.y * V.x);
            normal = ofVec3f(xn,yn,zn);
            normal.normalize();
            mesh.addNormal(normal);
            mesh.addNormal(normal);
            mesh.addNormal(normal);
        }
    }

    // Give shader access to cartesian coords
    // https://forum.openframeworks.cc/t/ofvbo-ofvbomesh-generic-attributes/9272/7
    shader.begin();
    int location = shader.getAttributeLocation("cartesianCoords");
    mesh.getVbo().setAttributeData(
                                   location,
                                   &(cartesianCoords[0].x),
                                   2,
                                   ySize * xSize * 6,
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
