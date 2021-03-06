#include "ofMain.h"
#include "ofApp.h"
#include "screenUtils.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,3);
    settings.setSize(1280, 360);
    settings.windowMode = OF_WINDOW;
    settings.multiMonitorFullScreen = false;

    ofCreateWindow(settings);
    logGlfwScreens();
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
