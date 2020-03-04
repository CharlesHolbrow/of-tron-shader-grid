//
//  Gen.hpp
//  grid-shader-t1
//
//  Created by Charles Holbrow on 3/3/20.
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
struct LerpD {
public:
    LerpD();
    double duration = 1;     // duration of lerp in seconds
    operator double() const; // cast to double
    double get() const;
    void setTarget(double target);
    void jumpTo(double value);

private:
    double initial = 0;
    double target = 0;
    uint64_t initialTime = 0;
    uint64_t targetTime = 0;
};

//--------------------------------------------------------------
struct GenSin {
public:
    double hz = 1;
    double max = 1;
    double min = -1;
    void advance(double deltaSeconds);
    operator double() const;
    double get() const;
    void setPeriod(double periodSeconds) { hz = 1./periodSeconds; };
private:
    double accumulator = 0;
    double value = 0; // before max|min
};

//--------------------------------------------------------------
struct GenTri {
    double hz = 1;
    double max = 1;
    double min = 0;
    void advance(double deltaSeconds);
    operator double() const;
    double get() const;
    void setPeriod(double periodSeconds) { hz = 1./periodSeconds; };
private:
    double accumulator = 0; // ramps 0 - 1
};

//--------------------------------------------------------------
struct GenSaw {
    double hz = 1;
    double min = 0; // should really be 'start'
    double max = 1; // should really be 'end'
    void advance(double deltaSeconds);
    explicit operator double() const;
    double get() const;
    void setPeriod(double periodSeconds) { hz = 1./periodSeconds; };
private:
    double accumulator = 0;
};
