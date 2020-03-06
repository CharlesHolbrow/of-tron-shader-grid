//
//  Logo.hpp
//  grid-shader-t1
//
//  Created by Charles Holbrow on 3/4/20.
//

#pragma once

#include "ofMain.h"
#include "Gen.h"

class Logo {
public:
    ofImage image;
    ofNode node;
    bool enabled;
    LerpD rotationSpeed;

    void setup();
    void update(double deltaSeconds);
    void draw();
};
