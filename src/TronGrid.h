#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "Gen.h"

class TronGrid
{
public:
    TronGrid();

    ~TronGrid();

    void resize(int xCells, int yCells, float cellSize);
    void draw();
    bool enabled = true;
    ofColor cT1 = ofColor(255, 255, 255);
    ofColor cF1 = ofColor(255, 255, 255);
    ofColor cT2 = ofColor(255, 255, 255);
    ofColor cF2 = ofColor(255, 255, 255);
    LerpD cLerp;
    void setTargetColors(ofColor c1, ofColor c2);

private:
    // How many quads in the x/y dimensions
    int xSize;
    int ySize;

    // How many vertices in the x/t dimensions
    int xVerts;
    int yVerts;
   
    float cellSize;

    ofVboMesh mesh;
    ofxAutoReloadedShader shader;
};

