#include "TronGrid.h"



TronGrid::TronGrid()
{
    shader.load("shadersGL3/grid");
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

    // Every Cell has two triangles with three vertices.
    vector<ofVec2f> gridPosition(xSize * ySize * 6, { 0, 0 });
    vector<ofVec3f> vertices(xVerts * yVerts);
    vector<ofVec3f> xDirection(xSize * ySize * 6, {0, 0, 0});
    vector<ofVec3f> yDirection(xSize * ySize * 6, {0, 0, 0});

    {
        int i = 0;
        for (int y = 0; y < yVerts; y++) {
            for (int x = 0; x < xVerts; x++) {
                float height = ofNoise(x * 0.05, y * 0.05);
                height = ofMap(height, 0.75, 1., 0., 8., true);
                ofVec3f vertex(x*cellSize, height, y*cellSize);
                vertices[i] = vertex;
                i++; 
            }
        }
    }


    // ofBook section on working with Meshes
    // https://openframeworks.cc/ofBook/chapters/generativemesh.html#basicsworkingwithofmesh
    // ofMesh docs:
    // https://openframeworks.cc/documentation/3d/ofMesh/
    mesh.enableNormals();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    int halfX = xSize / 2;
    int halfY = ySize / 2;
    int i = 0;
    int j = 0;
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            // Assume X increases right, y increases 'up'
            // ^
            // |
            // Y
            // + X--->
            int a = y * xVerts + x;  // vertex index of bottom left of cell
            int b = a + xVerts + 1;  // vertex index of upper right of cell
            int c = a + 1;           // vertex index of bottom right of cell
            int d = b - 1;           // vertex index of upper left of cell
            float gridX = x - halfX; // center the grid (x-axis)
            float gridY = y - halfY; // center the grid (y-axis)
            int ii = i;              // initial i value

            ofVec3f v0 = vertices[a];
            ofVec3f v1 = vertices[b];
            ofVec3f v2 = vertices[d];
            mesh.addVertex(v0);
            mesh.addVertex(v1);
            mesh.addVertex(v2);
            gridPosition[i++] = { gridX, gridY };
            gridPosition[i++] = { gridX + 1, gridY + 1 };
            gridPosition[i++] = { gridX, gridY + 1 };

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

            ofVec3f v3 = vertices[a];
            ofVec3f v4 = vertices[a + 1];
            ofVec3f v5 = vertices[b];
            mesh.addVertex(v3);
            mesh.addVertex(v4);
            mesh.addVertex(v5);
            gridPosition[i++] = { gridX, gridY };
            gridPosition[i++] = { gridX + 1, gridY };
            gridPosition[i++] = { gridX + 1, gridY + 1 };

            // normal for t2
            U = v4 - v3;
            V = v5 - v3;
            xn = (U.y * V.z) - (U.z * V.y);
            yn = (U.z * V.x) - (U.x * V.z);
            zn = (U.x * V.y) - (U.y * V.x);
            normal = ofVec3f(xn, yn, zn);
            normal.normalize();
            mesh.addNormal(normal);
            mesh.addNormal(normal);
            mesh.addNormal(normal);

            ofVec3f xDir = vertices[c] - vertices[a];
            ofVec3f yDir = vertices[b] - vertices[d];
            for (int k = 0; k < 6; k++) {
                xDirection[ii+k] = xDir;
                yDirection[ii+k] = yDir;
            }
        }
    }

    // Give shader access to cartesian coords
    // https://forum.openframeworks.cc/t/ofvbo-ofvbomesh-generic-attributes/9272/7
    shader.begin();
    int location = shader.getAttributeLocation("gridPosition");
    mesh.getVbo().setAttributeData(
        location,
        &(gridPosition[0].x),
        2,
        ySize * xSize * 6,
        GL_DYNAMIC_DRAW,
        sizeof(ofVec2f));
    location = shader.getAttributeLocation("xDirection");
    mesh.getVbo().setAttributeData(location, &(xDirection[0].x), 3, ySize * xSize * 6, GL_DYNAMIC_DRAW, sizeof(ofVec3f));
    location = shader.getAttributeLocation("yDirection");
    mesh.getVbo().setAttributeData(location, &(yDirection[0].x), 3, ySize * xSize * 6, GL_DYNAMIC_DRAW, sizeof(ofVec3f));
    shader.end();
}

void TronGrid::draw() {
    ofPushMatrix();
    ofTranslate({xSize * cellSize * -0.5, 0, ySize * cellSize * -0.5});
    shader.begin();
    shader.setUniform2f("screenSize", { ofGetWidth(), ofGetHeight() });
    shader.setUniform1f("time", ofGetElapsedTimef());
    mesh.draw();
    shader.end();
    ofPopMatrix();
}
