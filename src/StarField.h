#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

class StarField {
public:
    void setup();
    // Draw the star field to the current renderer.
    void draw(ofCamera cam, int fboWidth, int fboHeight);

    ofxAutoReloadedShader starShader;
    vector<ofVec3f> starPositions;
    ofVbo stars;
};
