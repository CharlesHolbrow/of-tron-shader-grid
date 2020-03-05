#include "StarField.h"

void StarField::setup() {

    starShader.load("shadersGL3/stargen");
    // randomly add a point on a sphere
    int   num = 500;
    for (int i = 0; i < num; i++) {

        float theta1 = ofRandom(0, TWO_PI);
        float theta2 = ofRandom(0, TWO_PI);

        ofVec3f p;
        p.x = cos(theta1) * cos(theta2);
        p.y = sin(theta1);
        p.z = cos(theta1) * sin(theta2);
        p *= ofRandom(40, 200); // radius
        starPositions.push_back(p);
    }
    int count = starPositions.size();
    stars.setVertexData(&starPositions[0], count, GL_DYNAMIC_DRAW);
}

void StarField::draw(ofCamera cam, int fboWidth, int fboHeight) {
    if (!enabled) return;

    starShader.begin();
    ofEnablePointSprites();
    glDepthMask(GL_FALSE); // don't write to the depth buffer (check only)
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // To calculate the size of the particle, the shader needs camera matrices
    // with no lens offset. I'm calling this the "simple projection matrix" and
    // "simple model view matrix".
    glm::vec2 lensOffset = cam.getLensOffset();
    cam.setLensOffset({0, 0});
    starShader.setUniformMatrix4f("smv", cam.getModelViewMatrix());
    starShader.setUniformMatrix4f("sp", cam.getProjectionMatrix());
    cam.setLensOffset(lensOffset);

    // Annoyingly, when a non-default VBO is active, shaders are not passed
    // accurate camera matrices, so I am manually passing in camera matrices.
    // Note that this means that we also have to manually flip the y-axis, which
    // openFrameworks usually manages for us. This is necessary because OF and
    // OpenGL use different coordinate conventions.
    glm::mat4x4 flipY;
    flipY[1][1] = -1.0;
    starShader.setUniform2f("screenSize", fboWidth, fboHeight);
    starShader.setUniformMatrix4f("mv", flipY * cam.getModelViewMatrix());
    starShader.setUniformMatrix4f("p", cam.getProjectionMatrix());
    ofSetColor(255, 0, 0);
    stars.draw(GL_POINTS, 0, starPositions.size());

    ofEnableBlendMode(OF_BLENDMODE_ALPHA); // TODO: double check if this is actually the default blend mode
    glDepthMask(GL_TRUE);
    ofDisablePointSprites();
    starShader.end();
}
