#pragma once

#include "ofMain.h"
#include "GLFW/glfw3.h"


////////////////////////////////////////////////////////////////////////////////
//
// Some utilities for finding and querying available screens.
// Note that these do not appear to work until affter ofCreateWindow was called
// (typicall ofCreateWindow is called in main.cpp)
//
// This post of the forums showed me how to get started querying screens:
// https://forum.openframeworks.cc/t/get-screen-size-of-second-monitor/14864/8
//
////////////////////////////////////////////////////////////////////////////////

struct ScreenInfo {
    int posX = 0;
    int posY = 0;
    int width = 0;
    int height = 0;
};

// use ofLog to print info about the screens
void logGlfwScreens();

vector<ScreenInfo> getScreens();
