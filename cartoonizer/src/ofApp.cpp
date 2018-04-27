#include "ofApp.h"
#include <iostream>


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    
    camWidth = 1280;    // try to grab at this size.
    camHeight = 720;
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    videoCartoonPixels = new unsigned char[camWidth * camHeight];
    cartoon.allocate(camWidth, camHeight, GL_LUMINANCE);

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
    
    ofSetHexColor(0xffffff);
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    ofImage img = pixelsRef; 
    cv::Mat samples(camHeight * camWidth, 3, CV_32FC2);
    
    for (int i = 0; i < camHeight; i++) {
        for (int j = 0; j < camWidth; j++) {
            float red = pixelsRef.getColor(i, j)[0];
            float green = pixelsRef.getColor(i, j)[1];
            float blue = pixelsRef.getColor(i, j)[2];
            
            samples.at<float>(i * j, 0) = red;
            samples.at<float>(i * j, 1) = green;
            samples.at<float>(i * j, 2) = blue;
        }
    }
    
    
    int clusterCount = 8;
    Mat labels;
    int attempts = 3;
    Mat centers;
    kmeans(samples, clusterCount, labels,
           TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
           3, KMEANS_PP_CENTERS, centers);
    
    
    int counter = 0;
    for (int i = 0; i < camHeight; i++) {
        for(int j = 0; j < camWidth; j++) {
            int cluster_idx = labels.at<int>(i + (j * camHeight), 0);
            int pixel = (centers.at<float>(cluster_idx, 0), centers.at<float>(cluster_idx, 1), centers.at<float>(cluster_idx, 2));
            videoCartoonPixels[counter] = pixel;
            counter++;
        }
    }
    
    cartoon.loadData(videoCartoonPixels, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_LUMINANCE);
    cartoon.draw(0, 0, 1280, 720);
        
    /*int counter = 0;
    for (int i = 0; i < camHeight; i++) {
        for (int j = 0; j < camWidth*3; j+=3) {
            
            int cluster_idx = labels.at<int>(j + (i * camWidth), 0);

            int grayPixel = (centers.at<float>(cluster_idx, 0), centers.at<float>(cluster_idx, 1), centers.at<float>(cluster_idx, 2));
            videoCartoonPixels[counter] = grayPixel;
            counter++;
        }
    }
    cartoon.loadData(videoCartoonPixels, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_LUMINANCE);
    cartoon.draw(0, 0, 640, 480);*/
   
    //vidGrabber.update();
    
    
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

