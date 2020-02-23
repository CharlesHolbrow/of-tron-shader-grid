#pragma once

#include "ofMain.h"
#include "GLFW/glfw3.h"


//--------------------------------------------------------------
//
// Some utilities for finding and querying available screens.
// Note that these do not appear to work until affter ofCreateWindow was called
// (typicall ofCreateWindow is called in main.cpp)
//
// This post of the forums showed me how to get started querying screens:
// https://forum.openframeworks.cc/t/get-screen-size-of-second-monitor/14864/8
//
//--------------------------------------------------------------
struct ScreenInfo {
    int posX = 0;
    int posY = 0;
    int width = 0;
    int height = 0;
};

struct VirtualScreen {
    ofFbo fbo;
    ofCamera cam;
    void setup (ofCamera& parentCam) {
        cam.setNearClip(parentCam.getNearClip());
        cam.setFarClip(parentCam.getFarClip());
        cam.setParent(parentCam);
    };

    void resize(int width, int height) {
        ofFboSettings settings;
        settings.numSamples = 4;
        settings.width = width;
        settings.height = height;
        settings.useDepth = true;
        //settings.internalformat
        fbo.clear();
        fbo.allocate(settings);
        cam.setAspectRatio((float)width/(float)height);
    };
    /// Clear the underlying fbo. IMPORTANT: call this outside of VirtualScreen's begin/end
    void clear() {
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();
    };
    void begin() {
        fbo.begin();
        cam.begin();
    }
    void end() {
        cam.end();
        fbo.end();
    }
};

// Print info about the screens via ofLog()
void logGlfwScreens();

vector<ScreenInfo> getScreens();

const char* getWindowModeString();
