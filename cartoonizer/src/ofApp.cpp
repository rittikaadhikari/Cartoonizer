#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    
    camWidth = 640;    // try to grab at this size.
    camHeight = 480;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,413);
    
    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,0);
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetHexColor(0xffffff);
    
    cv::Mat samples(camWidth * camHeight, 3, CV_32F);
    
    for (int i = 0; i < camWidth; i++) {
        for (int j = 0; j < camHeight; j++) {
            for (int k = 0; k < 3; k++) {
                samples.at<float>(i + (j * camWidth), k);
            }
        }
    }
    
    int clusterCt = 15;
    cv::Mat labels;
    int attempts = 5;
    cv::Mat centers;
    kmeans(samples, clusterCt, labels, cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, cv::KMEANS_PP_CENTERS, centers);
    
    for (int i = 0; i < camWidth; i++) {
        for (int j = 0; j < camHeight; j++) {
            int cluster_idx = labels.at<int>(j + (i * camWidth), 0);
            //pixelsRef.setColor(i, j, ofColor(centers.at<float>(cluster_idx, 0), centers.at<float>(cluster_idx, 1), centers.at<float>(cluster_idx, 2)));
            //std::cout << centers.at<float>(cluster_idx, 0) << std::endl;
        }
    }
    
    vidGrabber.update();
    
    /*for (int i = 0; i < camWidth; i+= 7){
         for (int j = 0; j < camHeight; j+= 9){
             // get the pixel and its lightness (lightness is the average of its RGB values)
             float lightness = pixelsRef.getColor(i,j).getLightness();
             // calculate the index of the character from our asciiCharacters array
             //int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
             // draw the character at the correct location
             //font.drawString(ofToString(asciiCharacters[character]), i, j);
         }
    }*/
    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    // in fullscreen mode, on a pc at least, the
    // first time video settings the come up
    // they come up *under* the fullscreen window
    // use alt-tab to navigate to the settings
    // window. we are working on a fix for this...
    
    if (key == 's' || key == 'S'){
        vidGrabber.videoSettings();
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

