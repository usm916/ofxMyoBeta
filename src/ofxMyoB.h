#pragma once

#include <myo/myo.hpp>
#include "ofMain.h"

#include "ofxMyoDataCollector.h"

enum MYO_STATE
{
    rest          = libmyo_pose_rest,
    fist          = libmyo_pose_fist,
    waveIn        = libmyo_pose_wave_in,
    waveOut       = libmyo_pose_wave_out,
    fingersSpread = libmyo_pose_fingers_spread,
    doubleTap     = libmyo_pose_double_tap,
    unknown       = libmyo_pose_unknown
};

class ofxMyoBeta
{
public:
    ofxMyoBeta(){}
    ~ofxMyoBeta(){}

    virtual void setup( string appName );
    virtual void update();
    virtual void debugDraw();
    
    virtual vector<int8_t> &getEmgArray();
    virtual MYO_STATE getMyoState();
    virtual ofVec3f &getOrientation();
    virtual ofVec3f &getAccelameter();

private:
    myo::Hub *hub;
    
    ofVec3f m_Orientation;
    ofVec3f m_Accelameter;
    
    ofxMyoDataCollector collector;
};




