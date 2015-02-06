#pragma once

#include "ofMain.h"
#include <myo/myo.hpp>

class DataCollector : public myo::DeviceListener {
public:
    DataCollector()
    : emgSamples()
    {
        emgSamples.assign(8, 0);
    }
    
    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp)
    {
        // We've lost a Myo.
        // Let's clean up some leftover state.
        emgSamples.clear();//fill(0);
        emgSamples.assign(8, 0);
    }
    
    // onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
    {
        for (int i = 0; i < 8; i++) {
            emgSamples[i] = emg[i];
        }
        hisEMG.push_back( emgSamples );
        if( hisEMG.size()>400 )
        {
            hisEMG.erase( hisEMG.begin() );
        }
    }
    
    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.
    
    // We define this function to print the current values that were updated by the on...() functions above.
    void print()
    {
        // Clear the current line
        std::cout << '\r';
        
        // Print out the EMG data.
        for (size_t i = 0; i < emgSamples.size(); i++) {
            std::ostringstream oss;
            oss << static_cast<int>(emgSamples[i]);
            std::string emgString = oss.str();
            
            std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
        }
        
        std::cout << std::flush;
    }
    
    void draw()
    {
        int pitchY = 100;
        ofSetColor(128,200,255);
        if(hisEMG.size())
        {
            for(int i=0;i<hisEMG.size()-1;i++)
            {
                for(int j=0;j<8;j++)
                {
                    ofLine(i*3,(j+1)*pitchY+hisEMG[i][j],(i+1)*3,(j+1)*pitchY+hisEMG[i+1][j]);
                }
            }
        }
    }
    
    vector< int8_t > &getEmgSamples(){ return emgSamples; }
    
    // The values of this array is set by onEmgData() above.
    vector< int8_t > emgSamples;
    vector< vector <int8_t> > hisEMG;
};

class ofxMyoBeta /*: public ofBaseApp */
{
public:
    ofxMyoBeta(){}
    ~ofxMyoBeta(){}

    void setup();
    void update();
    void draw();
    
    myo::Hub *hub;
    DataCollector collector;
};




