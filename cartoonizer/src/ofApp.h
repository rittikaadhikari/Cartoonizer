#pragma once
#include "ofxOpenCv.h"
#include "ofMain.h"

using namespace cv;

enum VideoState {
    VIDEO = 0,
    PAUSE,
    QUIT,
    SAVE
};

class ofApp : public ofBaseApp{

private:
    VideoState current_state_ = VIDEO;
    void saveScreen();
    
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
    
    ofVideoGrabber vidGrabber;
    ofTexture cartoon;
    unsigned char * videoCartoonPixels;
    int camWidth;
    int camHeight;
    
    
};
