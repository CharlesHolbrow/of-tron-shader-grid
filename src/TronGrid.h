#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

class TronGrid
{
public:
    TronGrid();

    ~TronGrid();

    void resize(int xCells, int yCells, float cellSize);
    void draw();

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

