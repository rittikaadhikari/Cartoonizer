#include "ofApp.h"
#include <iostream>

static int num_pictures = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Cartoonizer");
    ofSetBackgroundColor(255, 255, 255);

    mySound.load("file.mp3", true);
    
    cam_width = 640;    // try to grab at this size.
    cam_height = 480;
    
    vid_grabber.setVerbose(true);
    vid_grabber.setup(cam_width, cam_height);
    texture_pixels = new unsigned char[cam_width * cam_height];
    texture.allocate(cam_width, cam_height, GL_LUMINANCE);

    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
    mySound.play();

    if (current_state_ == VIDEO) {
        vid_grabber.update();
    } else if (current_state_ == PAUSE) {
        
    } else if (current_state_ == SAVE) {
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == QUIT) {
        vid_grabber.close();
    } else if (current_state_ == GRAYSCALE) {
        drawGrayscale();
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == CARTOONIZE) {
        drawCartoonize();
        saveScreen();
        current_state_ = PAUSE;
    }
    
}


//--------------------------------------------------------------
void ofApp::drawGrayscale() {
    ofImage img = vid_grabber.getPixels();
    int counter = 0;
    for (int i = 0; i < cam_height; i++) {
        for (int j = 0; j < cam_width*3; j+=3) {
            // get r, g and b components
            int r = (i*cam_width*3) + j;
            int g = (i*cam_width*3) + (j+1);
            int b = (i*cam_width*3) + (j+2);
            
            int grayPixel = (11 * img.getPixels()[r] + 16 * img.getPixels()[g] + 5 * img.getPixels()[b]) / 32;
            texture_pixels[counter] = grayPixel;
            counter++;
            
            
        }
    }
    
    texture.loadData(texture_pixels, vid_grabber.getWidth(), vid_grabber.getHeight(), GL_LUMINANCE);
    texture.draw(0, 0, cam_width, cam_height);
    vid_grabber.update();
}

//--------------------------------------------------------------
void ofApp::drawCartoonize() {
    ofPixels pixels_ref = vid_grabber.getPixels();
    
    cv::Mat samples = Mat::zeros(cam_height * cam_width, 5, CV_32F);
    
    for (int i = 0; i < cam_height * cam_width; i++) {
        samples.at<float>(i, 0) = (i % cam_width) / cam_height;
        samples.at<float>(i, 1) = (i / cam_width) / cam_width;
        
        // normalize colors
        samples.at<float>(i, 2) = pixels_ref.getColor(i)[0] / 255.0;
        samples.at<float>(i, 3) = pixels_ref.getColor(i)[1] / 255.0;
        samples.at<float>(i, 4) = pixels_ref.getColor(i)[2] / 255.0;
        
    }
    
    
    int cluster_count = 12;
    Mat labels;
    int attempts = 3;
    Mat centers;
    
    // add constants as params
    kmeans(samples, cluster_count, labels,
           TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
           attempts, KMEANS_PP_CENTERS, centers);
    
    int colors[cluster_count];
    for (int i = 0; i < cluster_count; i++) {
        colors[i] = 255 / (i + 1);
    }
    
    int counter = 0;
    
    for (int i = 0; i < cam_width * cam_height; i++) {
        texture_pixels[i] = (colors[labels.at<int>(0,i)]) ;
    }
    
    texture.loadData(texture_pixels, vid_grabber.getWidth(), vid_grabber.getHeight(), GL_LUMINANCE);
    texture.draw(0, 0, cam_width, cam_height);
    
    vid_grabber.update();
}

//--------------------------------------------------------------
void ofApp::saveScreen() {
    ofImage img = vid_grabber.getPixels();
    img.save("screengrab" + std::to_string(num_pictures) + ".png");
    num_pictures++;
}


//--------------------------------------------------------------
void ofApp::draw(){
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,413);
    
    // draw the raw video frame with the alpha value generated above
    vid_grabber.draw(0,0);
    
    ofSetHexColor(0xffffff);
    
    ofPixelsRef pixelsRef = vid_grabber.getPixels();
    ofImage img = pixelsRef;
    
    
    
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
    } else if (key == 'v' || key == 'V') {
        current_state_ = VIDEO;
        update();
    } else if (key == 'g' || key == 'G') {
        current_state_ = GRAYSCALE;
        update();
    } else if (key == 'c' || key == 'C') {
        current_state_ = CARTOONIZE;
        update();
    } else if (key == 'i' || key == 'I') {
        current_state_ = ILLINIFY;
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

