//
//  Logo.cpp
//  grid-shader-t1
//
//  Created by Charles Holbrow on 3/4/20.
//

#include "Logo.h"

void Logo::setup() {
    image.load("space-glam.png");
    node.setScale(48);
    node.move(0, 2, 0);
}

void Logo::update(double deltaSeconds) {
    node.rotateDeg(rotationSpeed.get() * deltaSeconds, {0, 1, 0});
}

void Logo::draw() {
    if (!enabled) return;

    float ar = (float)image.getWidth() / (float)image.getHeight();

    ofSetColor(255);
    ofPushMatrix();
    ofMultMatrix(node.getGlobalTransformMatrix());
    image.draw({-0.5, -0.5/ar, 0}, 1, 1/ar);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); // TODO: double check if this is actually the default blend mode
    ofPopMatrix();
}
