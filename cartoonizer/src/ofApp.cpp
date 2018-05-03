#include "ofApp.h"
#include <iostream>

static int num_pictures = 0;


//--------------------------------------------------------------
void ofApp::setup(){
    // sets up the window
    ofSetWindowTitle("Cartoonizer");
    ofSetBackgroundColor(0, 0, 0);
    
    // initialize camera
    cam_width_ = 640;
    cam_height_ = 480;
    vid_grabber_.setVerbose(true);
    vid_grabber_.setup(cam_width_, cam_height_);
    
    // loads a font
    font_.load(font_path_, 9);

    // loads the music
    background_sound_.load(ready_for_it_path_);
    background_sound_.setLoop(true);
    background_sound_.play();

    // allocates texture to use (i.e. overlays)
    texture_pixels_ = new unsigned char[cam_width_ * cam_height_];
    texture_.allocate(cam_width_, cam_height_, GL_LUMINANCE);
    

    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
    // checks each state and calls the corresponding action
    if (current_state_ == VIDEO) {
        texture_ = vid_grabber_.getTexture();
        vid_grabber_.update();
    } else if (current_state_ == SAVE) {
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == QUIT) {
        vid_grabber_.close();
    } else if (current_state_ == GRAYSCALE) {
        drawGrayscale();
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == CARTOONIZE) {
        drawCartoonize(10, 5);
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == ILLINIFY) {
        drawIllinify();
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == BLUESCREEN) {
        drawBluescreen();
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == GREENSCREEN) {
        drawGreenscreen();
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == REDSCREEN) {
        drawRedscreen();
        saveScreen();
        current_state_ = PAUSE;
    } else if (current_state_ == DEMO) {
        demo();
    }
    
}

//--------------------------------------------------------------
void ofApp::drawIllinify() {
    ofImage img = vid_grabber_.getPixels();
    int counter = 0;
    
    // creating a temporary image to "illinify" the image
    // pixel by pixel
    ofImage temp;
    temp.allocate(cam_width_, cam_height_, OF_IMAGE_COLOR);
    temp.setColor(255, 255, 255);
    
    // looping through each pixel and checking whether we should
    // enhance the illini blue or the illini orange
    for (int i = 0; i < cam_width_ * cam_height_; i++) {
        int x = i % cam_width_;
        int y = i / cam_width_;
        
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
        
        // setting a new color for this pixel
        ofColor new_color;
        new_color.setHsb(hue, saturation, brightness);
        temp.setColor(x, y, new_color);
        
    }
    
    // overlaying the texture with the new illinified colors
    texture_.loadData(temp.getPixels());
    texture_.draw(0, 0, cam_width_, cam_height_);
}

//--------------------------------------------------------------
void ofApp::drawBluescreen() {
    ofImage img = vid_grabber_.getPixels();
    
    // creating a temp image to contain the greenscreen
    // because texture_pixels doesn't accept ofPixels
    ofImage temp;
    temp.allocate(cam_width_, cam_height_, OF_IMAGE_COLOR);
    temp.setColor(ofColor::white);
    
    // loops through the image and converts image colors
    // to focus on blue
    int counter = 0;
    for (int i = 0; i < cam_width_ * cam_height_; i++) {
        int x = i % cam_width_;
        int y = i / cam_width_;
        
        ofColor color = img.getColor(x, y);
        color.r = 0;
        color.g = 0;
        temp.setColor(x, y, color);
        
    }
    
    // loads the data to the texture and displays
    texture_.loadData(temp.getPixels());
    texture_.draw(0, 0, cam_width_, cam_height_);
}

//--------------------------------------------------------------
void ofApp::drawRedscreen() {
    ofImage img = vid_grabber_.getPixels();
    
    // creating a temp image to contain the greenscreen
    // because texture_pixels doesn't accept ofPixels
    ofImage temp;
    temp.allocate(cam_width_, cam_height_, OF_IMAGE_COLOR);
    temp.setColor(ofColor::white);
    
    // loops through the image and converts image colors
    // to focus on red
    int counter = 0;
    for (int i = 0; i < cam_width_ * cam_height_; i++) {
        int x = i % cam_width_;
        int y = i / cam_width_;
        
        ofColor color = img.getColor(x, y);
        color.b = 0;
        color.g = 0;
        temp.setColor(x, y, color);
        
    }
    
    // loads the data to the texture and displays
    texture_.loadData(temp.getPixels());
    texture_.draw(0, 0, cam_width_, cam_height_);
}

//--------------------------------------------------------------
void ofApp::drawGreenscreen() {
    ofImage img = vid_grabber_.getPixels();
    
    // creating a temp image to contain the greenscreen
    // because texture_pixels doesn't accept ofPixels
    ofImage temp;
    temp.allocate(cam_width_, cam_height_, OF_IMAGE_COLOR);
    temp.setColor(ofColor::white);
    
    // loops through the image and converts image colors
    // to focus on green
    int counter = 0;
    for (int i = 0; i < cam_width_ * cam_height_; i++) {
        int x = i % cam_width_;
        int y = i / cam_width_;
        
        ofColor color = img.getColor(x, y);
        color.b = 0;
        color.r = 0;
        temp.setColor(x, y, color);
        
    }
    
    // loads the data to the texture and displays
    texture_.loadData(temp.getPixels());
    texture_.draw(0, 0, cam_width_, cam_height_);
}


//--------------------------------------------------------------
void ofApp::drawGrayscale() {
    ofImage img = vid_grabber_.getPixels();
    
    // loops through the image and converts to grayscale
    int counter = 0;
    for (int i = 0; i < cam_width_ * cam_height_; i++) {
        int x = i % cam_width_;
        int y = i / cam_width_;
        
        ofColor color = img.getColor(x, y);
        int grayPixel = (color.r + color.g + color.b) / 3;
        texture_pixels_[counter++] = grayPixel;
        
    }
    
    // load the data to the texture
    texture_.loadData(texture_pixels_, vid_grabber_.getWidth(), vid_grabber_.getHeight(), GL_LUMINANCE);
    texture_.draw(0, 0, cam_width_, cam_height_);
}

//--------------------------------------------------------------
void ofApp::drawCartoonize(int cluster_count, int attempts) {
    ofPixels pixels_ref = vid_grabber_.getPixels();
    
    // collecting samples from the data
    cv::Mat samples = Mat::zeros(cam_height_ * cam_width_, 5, CV_32F);
    ofImage img = pixels_ref;
    for (int y = 0; y < cam_height_; y++)  {
        for (int x = 0; x < cam_width_; x++)  {
            samples.at<float>(x + y * cam_width_, 0) = (float)x / cam_width_ / cam_height_;
            samples.at<float>(x + y * cam_width_, 1) = y % (int)cam_width_ / cam_width_;
            
            // accessing the RGB components of the x, y pixel
            samples.at<float>(x + y * cam_width_, 2) = (float)img.getColor(x, y).r / 255.0f;
            samples.at<float>(x + y * cam_width_, 3) = (float)img.getColor(x, y).g / 255.0f;
            samples.at<float>(x + y * cam_width_, 4) = (float)img.getColor(x, y).b / 255.0f;
        }
    }
    
    // performing KMeans on the data
    Mat labels;
    TermCriteria criteria = TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0);
    Mat centers;
    
    kmeans(samples, cluster_count, labels, criteria,
           attempts, KMEANS_PP_CENTERS, centers);
    
    // extracting the proper colors
    int colors[cluster_count];
    for (int i = 0; i < cluster_count; i++) {
        colors[i] = 255 / (i + 1);
    }
    
    
    // setting the texture to have the correct pixels
    for (int y = 0; y < cam_height_; y++)  {
        for (int x = 0; x < cam_width_; x++)  {
            int index = y * cam_width_ + x;
            int cluster_index = labels.at<int>(index, 0);
            
            texture_pixels_[x + y * cam_width_] = colors[cluster_index];
        }
    }
    
    // loads the data to the texture and displays
    texture_.loadData(texture_pixels_, vid_grabber_.getWidth(), vid_grabber_.getHeight(), GL_LUMINANCE);
    texture_.draw(0, 0, cam_width_, cam_height_);
}

//--------------------------------------------------------------
void ofApp::demo() {
    vid_grabber_.update();
    
    // calling with less attempts to reduce lag: look into threading
    // for more effectiveness
    drawCartoonize(10, 2);
}

//--------------------------------------------------------------
void ofApp::saveScreen() {
    // saves the current screen and updates number of pictures taken.
    if (current_state_ == PAUSE || current_state_ == VIDEO) {
        ofImage img = vid_grabber_.getPixels();
        img.save("images/screengrab" + std::to_string(num_pictures) + ".png");
        num_pictures++;
    } else {
        ofImage img;
        texture_.readToPixels(img.getPixels());
        img.save("images/screengrab" + std::to_string(num_pictures) + ".png");
        num_pictures++;
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    // set a white fill color with the alpha generated above
    ofSetColor(255,255,255,413);
    
    // draw the raw video frame with the alpha value generated above
    texture_.draw(0, 0, cam_width_, cam_height_);
    ofSetHexColor(0xffffff);
        
    ofPixelsRef pixelsRef = vid_grabber_.getPixels();
    ofImage img = pixelsRef;

    
    // drawing commands box at the top
    ofSetColor(ofColor::white);
    ofRectangle myRect(0, 0, cam_width_, 45);
    ofDrawRectangle(myRect);
    ofSetColor(0, 0, 0);
    
    string commands = "COMMANDS:\nC - Cartoonize R - Redscreen E - Emeraldscreen B - Bluescreen\nG - Grayscale I - Illinify";
    commands += " V - Video P - Pause S - Save Q - Quit";
    font_.drawString(commands, 15, 15);
}

//--------------------------------------------------------------
void ofApp::playSong(string path) {
    background_sound_.unload();
    background_sound_.load(path);
    background_sound_.setLoop(true);
    background_sound_.play();}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // checks your key press to determine which state to set
    // current_state_ to
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
    } else if (key == 'b' || key == 'B') {
        current_state_ = BLUESCREEN;
        update();
    } else if (key == 'e' || key == 'E') {
        current_state_ = GREENSCREEN;
        update();
    } else if (key == 'r' || key == 'R') {
        current_state_ = REDSCREEN;
        update();
    } else if (key == 'd' || key == 'D') {
        current_state_ = DEMO;
        update();
    } else if (key == '1') {
        playSong(ready_for_it_path_);
    } else if (key == '2') {
        playSong(havana_path_);
    } else if (key == '3') {
        playSong(despacito_path_);
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

