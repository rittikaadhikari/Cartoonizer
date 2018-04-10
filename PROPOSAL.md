# Project Proposal: SP18, Software Design Studio

## Cartoonizer
For my final project, I want to take it all the way back to the old days of PhotoBooth. I fondly remember using PhotoBooth for all of its wacky filters and as a general means to waste time in middle school. Now, I want to create an open frameworks application that accesses your laptop's webcam and cartoonizes your face in real-time. 

### How Can I Get Started? 
#### Webcam Interface
In order to create this Cartoonizer, I need to be able to easily access the device's built-in or external webcam. In order to be able to access the webcam's stream, I plan on creating an instance of **ofVideoGrabber**. This just wraps QuickTime's sequence-grabbing-component to provide low level access to the webcam. Now that I can directly access my webcam stream, I plan on using **ofPixels** to load the pixels from each frame of the video.


