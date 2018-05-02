#include "ofApp.h"
#include <iostream>

static int num_pictures = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Cartoonizer");
    ofSetBackgroundColor(255, 255, 255);

    mySound.load("01 ...Ready For It_.mp3");
    mySound.play();

    
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

    if (current_state_ == VIDEO) {
        texture = vid_grabber.getTexture();
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
    } else if (current_state_ == ILLINIFY) {
        drawIllinify();
        saveScreen();
        current_state_ = PAUSE;
    }
    
}

//--------------------------------------------------------------
void ofApp::drawIllinify() {
    ofImage img = vid_grabber.getPixels();
    int counter = 0;
    
    ofImage temp;
    temp.allocate(cam_width, cam_height, OF_IMAGE_COLOR);
    temp.setColor(ofColor::white);
    for (int i = 0; i < cam_width * cam_height; i++) {
        int x = i % cam_width;
        int y = i / cam_width;
        
        ofColor color = img.getColor(x, y);
        float hue, saturation, brightness;
        color.getHsb(hue, saturation, brightness);
        
        double illini_orange = 11;
        double illini_blue = 216;
        double dist_orange = 0;
        double dist_blue = 0;
        
        // finding the distance from orange hue vs. distance from blue hue
        if (hue > illini_blue) {
            dist_orange = (360 + illini_orange) - hue;
            dist_blue = hue - illini_blue;
        } else if (hue >= illini_orange and hue <= illini_blue) {
            dist_orange = hue - illini_orange;
            dist_blue = illini_blue - hue;
        } else {
            dist_orange = illini_orange - hue;
            dist_blue = (360 - illini_blue) + hue;
        }
        
        // assign new hue to pixel
        if (dist_orange < dist_blue) {
            hue = illini_orange;
        } else {
            hue = illini_blue;
        }
        
        ofColor new_color;
        new_color.setHsb(hue, saturation, brightness);
        temp.setColor(x, y, new_color);
        
    }
    
    texture.loadData(temp.getPixels());
    texture.draw(0, 0, cam_width, cam_height);
}


//--------------------------------------------------------------
void ofApp::drawGrayscale() {
    ofImage img = vid_grabber.getPixels();
    int counter = 0;
    
    for (int i = 0; i < cam_width * cam_height; i++) {
        int x = i % cam_width;
        int y = i / cam_width;
        
        ofColor color = img.getColor(x, y);
        int grayPixel = (color.r + color.g + color.b) / 3;
        texture_pixels[counter++] = grayPixel;
        
    }
    
    texture.loadData(texture_pixels, vid_grabber.getWidth(), vid_grabber.getHeight(), GL_LUMINANCE);
    texture.draw(0, 0, cam_width, cam_height);
}

//--------------------------------------------------------------
void ofApp::drawCartoonize() {
    ofPixels pixels_ref = vid_grabber.getPixels();
    
    cv::Mat samples = Mat::zeros(cam_height * cam_width, 3, CV_32F);
    ofImage img = pixels_ref;
    for (int y = 0; y < cam_height; y++)  {
        for (int x = 0; x < cam_width; x++)  {
            samples.at<float>(x + y * cam_width, 0) = (float)x / cam_width / cam_height;
            samples.at<float>(x + y * cam_width, 1) = y % (int)cam_width / cam_width;
            samples.at<float>(x + y * cam_width, 2) = (float)img.getColor(x, y).r / 255.0f;
            samples.at<float>(x + y * cam_width, 3) = (float)img.getColor(x, y).g / 255.0f;
            samples.at<float>(x + y * cam_width, 4) = (float)img.getColor(x, y).b / 255.0f;
        }
    }
    
    int cluster_count = 10;
    Mat labels;
    int attempts = 5;
    Mat centers;
    
    // add constants as params
    kmeans(samples, cluster_count, labels,
           TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
           attempts, KMEANS_PP_CENTERS, centers);
    
    int colors[cluster_count];
    for (int i = 0; i < cluster_count; i++) {
        colors[i] = 255 / (i + 1);
    }
    
    for (int y = 0; y < cam_height; y++)  {
        for (int x = 0; x < cam_width; x++)  {
            int index = y * cam_width + x;  // This corresponds to pixel_index above
            int cluster_index = labels.at<int>(index, 0); // 0 to 7 in your case
            
            texture_pixels[x + y * cam_width] = colors[cluster_index];
        }
    }
    
    texture.loadData(texture_pixels, vid_grabber.getWidth(), vid_grabber.getHeight(), GL_LUMINANCE);
    texture.draw(0, 0, cam_width, cam_height);
}

//--------------------------------------------------------------
void ofApp::saveScreen() {
    if (current_state_ == PAUSE || current_state_ == VIDEO) {
        ofImage img = vid_grabber.getPixels();
        img.save("screengrab" + std::to_string(num_pictures) + ".png");
        num_pictures++;
    } else {
        ofImage img;
        texture.readToPixels(img.getPixels());
        img.save("screengrab" + std::to_string(num_pictures) + ".png");
        num_pictures++;
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,413);
    
    // draw the raw video frame with the alpha value generated above
    texture.draw(0, 0, cam_width, cam_height);
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

