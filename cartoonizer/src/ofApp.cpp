#include "ofApp.h"
#include <iostream>

static int num_pictures = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Cartoonizer");
    ofSetBackgroundColor(255, 255, 255);
    
    camWidth = 640;    // try to grab at this size.
    camHeight = 480;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    videoCartoonPixels = new unsigned char[camWidth * camHeight];
    cartoon.allocate(camWidth, camHeight, GL_LUMINANCE);

    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
    if (current_state_ == VIDEO) {
        vidGrabber.update();
    } else if (current_state_ == PAUSE) {
    } else if (current_state_ == SAVE) {
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == QUIT) {
        vidGrabber.close();
    }
    
}


//--------------------------------------------------------------
void ofApp::saveScreen() {
    ofImage img = vidGrabber.getPixels();
    img.save("screengrab" + std::to_string(num_pictures) + ".png");
    num_pictures++;
}


//--------------------------------------------------------------
void ofApp::draw(){
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,413);
    
    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,0);
    
    ofSetHexColor(0xffffff);
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    ofImage img = pixelsRef;
    
    
    
    
    /*cv::Mat samples = Mat::zeros(camHeight * camWidth, 5, CV_32F);
    
    for (int i = 0; i < camHeight * camWidth; i++) {
        samples.at<float>(i, 0) = (i / camWidth) / camHeight;
        samples.at<float>(i, 1) = (i % camWidth) / camWidth;
        
        // normalize colors
        samples.at<float>(i, 2) = pixelsRef.getColor(i)[0] / 255.0;
        samples.at<float>(i, 3) = pixelsRef.getColor(i)[1] / 255.0;
        samples.at<float>(i, 4) = pixelsRef.getColor(i)[2] / 255.0;
        
    }
    
    
    int clusterCount = 12;
    Mat labels;
    int attempts = 3;
    Mat centers;
    
    // add constants as params
    kmeans(samples, clusterCount, labels,
           TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
           attempts, KMEANS_PP_CENTERS, centers);
    
    int colors[clusterCount];
    for (int i = 0; i < clusterCount; i++) {
        colors[i] = 255 / (i + 1);
    }
    
    int counter = 0;
    
    for (int i = 0; i < camWidth * camHeight; i++) {
        videoCartoonPixels[i] = (colors[labels.at<int>(0,i)]) ;
    }
    
    cartoon.loadData(videoCartoonPixels, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_LUMINANCE);
    cartoon.draw(0, 0, 640, 480);
    
    vidGrabber.update();*/
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...
    
    if (key == 'p' || key == 'P') {
        current_state_ = (current_state_ == PAUSE) ? VIDEO:PAUSE;
        update();
    } else if (key == 'q' || key == 'Q') {
        current_state_ = QUIT;
        update();
    } else if (key == 's' || key == 'S') {
        current_state_ = SAVE;
        update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

