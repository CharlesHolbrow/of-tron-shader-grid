#include "screenUtils.h"


void logGlfwScreens() {

    auto screens = getScreens();
    ofLog() << "Found " << screens.size() << " screens";
    int i = 0;
    for (auto screen : screens) {
        ofLog() << "Screen " << i++ << " size: " << screen.width << "x" << screen.height;
        ofLog() << "  position: " << screen.posX << ", " << screen.posY;
    }
}

vector<ScreenInfo> getScreens() {
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    vector<ScreenInfo> screens;
    for (int i = 0; i < count; i++) {
        ScreenInfo screen;
        
        glfwGetMonitorPos(monitors[i], &screen.posX, &screen.posY); // We take the second monitor
        const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[i]);
        screen.height = desktopMode->height;
        screen.width = desktopMode->width;
        screens.push_back(screen);
    }
    return screens;
}

char* getWindowModeString() {
    int mode = ofGetWindowMode();
    switch (mode) {
    case OF_WINDOW:
        return "OF_WINDOW";
        break;
    case OF_FULLSCREEN:
        return "OF_FULLSCREEN";
        break;
    case OF_GAME_MODE:
        return "OF_GAME_MODE";
        break;
    }
    return "UNKNOWN";
}