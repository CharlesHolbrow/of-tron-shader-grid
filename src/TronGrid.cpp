#include "TronGrid.h"



TronGrid::TronGrid()
{
    shader.load("shadersGL2/shader");
}


TronGrid::~TronGrid()
{
}


void TronGrid::resize(int xCells, int yCells, float _cellSize) {
    xSize = xCells;
    ySize = yCells;
    xVerts = xCells + 1;
    yVerts = yCells + 1;
    cellSize = _cellSize;

    vector<ofVec2f> cartesianCoords(xSize * ySize * 6, { 0, 0 });
    vector<ofVec3f> vertices(xVerts * yVerts);
    {
        int i = 0;
        for (int y = 0; y < yVerts; y++) {
            for (int x = 0; x < xVerts; x++) {
                float height = ofNoise(x * 0.05, y * 0.05);
                height = ofMap(height, 0.75, 1., 0., 400., true);
                ofVec3f vertex(x*cellSize, height, y*cellSize);
                vertices[i++] = vertex;
            }
        }
    }

    // ofBook section on working with Meshes
    // https://openframeworks.cc/ofBook/chapters/generativemesh.html#basicsworkingwithofmesh
    // ofMesh docs:
    // https://openframeworks.cc/documentation/3d/ofMesh/
    mesh.enableNormals();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    int i = 0;
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            int a = y * xVerts + x;
            int b = a + xVerts + 1;

            ofVec3f v0 = vertices[a];
            ofVec3f v1 = vertices[b];
            ofVec3f v2 = vertices[b - 1];
            mesh.addVertex(v0);
            mesh.addVertex(v1);
            mesh.addVertex(v2);
            cartesianCoords[i++] = { v0.x / cellSize, v0.z / cellSize };
            cartesianCoords[i++] = { v1.x / cellSize, v1.z / cellSize };
            cartesianCoords[i++] = { v2.x / cellSize, v2.z / cellSize };

            // Simple normals https://forum.openframeworks.cc/t/solved-how-to-properly-calculate-normals-of-the-box/25487
            // normal for t1
            ofVec3f U = v1 - v0;
            ofVec3f V = v2 - v0;
            float xn = (U.y * V.z) - (U.z * V.y);
            float yn = (U.z * V.x) - (U.x * V.z);
            float zn = (U.x * V.y) - (U.y * V.x);
            ofVec3f normal = ofVec3f(xn, yn, zn);
            normal.normalize();
            mesh.addNormal(normal);
            mesh.addNormal(normal);
            mesh.addNormal(normal);

            v0 = vertices[a];
            v1 = vertices[a + 1];
            v2 = vertices[b];
            mesh.addVertex(v0);
            mesh.addVertex(v1);
            mesh.addVertex(v2);
            cartesianCoords[i++] = { v0.x / cellSize, v0.z / cellSize };
            cartesianCoords[i++] = { v1.x / cellSize, v1.z / cellSize };
            cartesianCoords[i++] = { v2.x / cellSize, v2.z / cellSize };

            // normal for t2
            U = v1 - v0;
            V = v2 - v0;
            xn = (U.y * V.z) - (U.z * V.y);
            yn = (U.z * V.x) - (U.x * V.z);
            zn = (U.x * V.y) - (U.y * V.x);
            normal = ofVec3f(xn, yn, zn);
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

void TronGrid::draw() {
    shader.begin();
    shader.setUniform2f("screenSize", { ofGetWidth(), ofGetHeight() });
    mesh.draw();
    shader.end();
}