//
//  Gen.cpp
//  grid-shader-t1
//
//  Created by Charles Holbrow on 3/3/20.
//

#include "Gen.h"

//--------------------------------------------------------------
LerpD::LerpD() {
    initialTime = ofGetElapsedTimeMicros();
    targetTime = initialTime;
}

LerpD& LerpD::operator=(const double _target) {
    double current = (double)*this;
    initial = current;
    initialTime = ofGetElapsedTimeMicros();
    target = _target;
    targetTime = initialTime + duration * 1000000;
    return *this;
}

LerpD::operator double() const {
    double amount = ofGetElapsedTimeMicros() - initialTime; // microseconds elapsed since start
    amount = amount / (duration * 1000000);                 // mapped between 0 and 1
    return ofLerp(initial, target, ofClamp(amount, 0, 1));
}

//--------------------------------------------------------------
void GenSin::advance(double deltaSeconds) {
    accumulator += deltaSeconds * hz * TWO_PI;
    accumulator = fmod(accumulator, TWO_PI);
    value = sin(accumulator);
}

GenSin::operator double() const {
    double range = abs(max-min);
    return (value  + 1) * 0.5 * range + MIN(max, min);
}

//--------------------------------------------------------------
void GenTri::advance(double deltaSeconds) {
    accumulator += deltaSeconds * hz;
    accumulator = fmod(accumulator, 1.0);
}

GenTri::operator double() const {
    double cut = MAX(0.0, accumulator - 0.5) * 2.0;
    double tri = accumulator - cut;
    return tri * 2 * abs(max-min) + MIN(max, min);
}

//--------------------------------------------------------------
void GenSaw::advance(double deltaSeconds) {
    accumulator = fmod(accumulator + deltaSeconds * hz, 1.0);
}

GenSaw::operator double() const {
    return ofMap(accumulator, 0, 1, min, max);
}
