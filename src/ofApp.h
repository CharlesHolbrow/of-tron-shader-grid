#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxAutoReloadedShader.h"
#include "TronGrid.h"
#include "StarField.h"
#include "screenUtils.h"
#include "Gen.h"
#include "Logo.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void handleOscMessage(const ofxOscMessage &msg);

    ofEasyCam cam;
    TronGrid grid;
    StarField stars;

    VirtualScreen vs0;
    VirtualScreen vs1;
    VirtualScreen vs2;
    bool twoScreenMode = false;
    bool resized = false;

    Logo logo;
    glm::vec3 upAxis = {0, 1, 0};

    // Generators
    GenSin v1;
    GenTri t1;
    GenSaw saw1;
    LerpD lerpZoom;
    LerpD orbitSpeed;
    float orbitRadians = 0;
    LerpD orbitAngle;
    float restingOrbitSpeed = 0;
    uint64_t lastFrameMicroseconds = 0;

    // OSC
    ofxOscReceiver receiver;
};
