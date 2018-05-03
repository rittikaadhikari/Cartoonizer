#pragma once
#include "ofxOpenCv.h"
#include "ofMain.h"

using namespace cv;

/**
 * This enum tracks the state of the video grabber application
 * at the moment.
 * @author Rittika Adhikari
 */
enum VideoState {
    VIDEO = 0,
    PAUSE,
    QUIT,
    SAVE,
    GRAYSCALE,
    CARTOONIZE,
    ILLINIFY,
    BLUESCREEN,
    REDSCREEN,
    GREENSCREEN,
    DEMO
};

/**
 * This application will display your face in different filters, depending
 * on which key you press.
 * @author Rittika Adhikari
 */
class ofApp : public ofBaseApp{

private:
    /**
     * Saves the current picture to the images folder as a screengrab.
     */
    void saveScreen();
    
    /**
     * Plays the requested song.
     */
    void playSong(string path);
    
    /**
     * Takes a picture of the user in grayscale.
     */
    void drawGrayscale();
    
    /**
     * Cartoonizes the current screen of the user.
     * @param cluster_count the number of clusters for kmeans
     * @param attempts the number of attempts for kmeans.
     */
    void drawCartoonize(int cluster_count, int attempts);
    
    /**
     * Illinifies a picture of the user.
     */
    void drawIllinify();
    
    /**
     * Draws the user in blue.
     */
    void drawBluescreen();
    
    /**
     * Draws the user in red.
     */
    void drawRedscreen();
    
    /**
     * Draws the user in green.
     */
    void drawGreenscreen();
    
    /**
     * The cartoonizer in video mode. (BETA)
     */
    void demo();
    
    // sets up the video
    ofVideoGrabber vid_grabber_;
    int cam_width_;
    int cam_height_;
    
    // sets current state to video
    VideoState current_state_ = VIDEO;
    
    // sets up the texture overlay
    ofTexture texture_;
    unsigned char * texture_pixels_;
    
    // for loading music & font
    ofSoundPlayer background_sound_;
    ofTrueTypeFont font_;
    
    // filepaths
    const string ready_for_it_path_ = "music/ready_for_it.mp3";
    const string havana_path_ = "music/havana.mp3";
    const string despacito_path_ = "music/despacito.mp3";
    const string font_path_ = "fonts/Courier New Bold.ttf";
    
public:
    
    /**
     * Sets up the video player and loads the font.
     */
    void setup();
    
    /**
     * Updates the video according to the current state.
     */
    void update();
    
    /**
     * Draws video screen alongside a commands box.
     */
    void draw();
    
    /**
     * Changes the state to the one corresponding to the key pressed.
     * @param key the key to do the action of.
     */
    void keyPressed(int key);
    
    // not used
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


    
};
