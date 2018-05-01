#pragma once
#include "ofxOpenCv.h"
#include "ofMain.h"

using namespace cv;

enum VideoState {
    VIDEO = 0,
    PAUSE,
    QUIT,
    SAVE,
    GRAYSCALE,
    CARTOONIZE,
    ILLINIFY
};

class ofApp : public ofBaseApp{

private:
    VideoState current_state_ = VIDEO;
    void saveScreen();
    void drawGrayscale();
    void drawCartoonize();
    
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
    
    ofVideoGrabber vid_grabber;
    ofTexture texture;
    unsigned char * texture_pixels;
    int cam_width;
    int cam_height;
    ofSoundPlayer mySound;

    
    
};
