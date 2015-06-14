
#include "ofxMyoB.h"

void ofxMyoBeta::setup( string appName )
{
    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    ofBackground(0);

    hub = new myo::Hub( appName );
    cout << "Attempting to find a Myo..." << endl;

    // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
    // immediately.
    // waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
    // if that fails, the function will return a null pointer.
    myo::Myo* myo = hub->waitForMyo( 10000 );

    // If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
    if(!myo)
    {
        throw std::runtime_error("Unable to find a Myo!");
    }

    // We've found a Myo.
    std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

    // Next we enable EMG streaming on the found Myo.
    myo->setStreamEmg(myo::Myo::streamEmgEnabled);

    // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.

    // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
    // Hub::run() to send events to all registered device listeners.
    hub->addListener( &collector );
}

//--------------------------------------------------------------
void ofxMyoBeta::update()
{
    // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
    // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
    hub->run(1000/60);
}

void ofxMyoBeta::debugDraw(){

    // After processing events, we call the print() member function we defined above to print out the values we've
    // obtained from any events that have occurred.

    // PRINTS DATA as numelcal params
    collector.print();
    
    // DRAW Collector waves
    collector.draw();
    
    // DRAW Orientation Axis. has not implemented yet.
    collector.drawAxis();
}

vector<int8_t> &ofxMyoBeta::getEmgArray()
{
    vector<int8_t> emgArr;
    return emgArr;
}

MYO_STATE ofxMyoBeta::getMyoState()
{
    return fist;
}

ofVec3f &ofxMyoBeta::getOrientation()
{
    return m_Orientation;
}

ofVec3f &ofxMyoBeta::getAccelameter()
{
    return m_Accelameter;
}



