#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

class StarField {
public:
    void setup();
    void draw(ofCamera cam);

    ofxAutoReloadedShader starShader;
    vector<ofVec3f> starPositions;
    ofVbo stars;
};