# Project Proposal: SP18, Software Design Studio

## Cartoonizer
For my final project, I want to take it all the way back to the old days of PhotoBooth. I fondly remember using PhotoBooth for all of its wacky filters and as a general means to waste time in middle school. Now, I want to create an open frameworks application that accesses your laptop's webcam, and will apply filters to your face & saves them, depending on what key you press! I also want to include a beta cartoonize-video mode. 

### How Can I Get Started? 
#### Webcam Interface
In order to create this Cartoonizer, I need to be able to easily access the device's built-in or external webcam. In order to be able to access the webcam's stream, I plan on creating an instance of **ofVideoGrabber**. This just wraps QuickTime's sequence-grabbing-component to provide low level access to the webcam. Now that I can directly access my webcam stream, I plan on using **ofPixels** to load the pixels from each frame of the video.
#### Cartoonize
The second (and final) component of the Cartoonizer would be to actually cartoonize each frame of the video! According to my research, the most viable way of doing this would be to use the K-Means clustering algorithm to color-quantize each pixel in order to get that cartoonized effect. I plan on using the **opencv** library, which includes a lot of useful algorithms, such as the K-Means clustering, to work on this color-clustering. Then, I would apply each cluster color to the corresponding group of pixels, using the **ofPixels** and then draw that image instead.
#### Extras? 
If I have additional time, I would probably try to add key-presses that will cartoonize in different image colors (i.e. - grayscale, sepia, illinified, etc.) In order to do this, I would just modify the HSLA values of the image first accordding to the type of key press, and then I would call my cartoonizing algorithm. I would probably also add in some funky music in the background that you could listen to as you Cartoonize :) If I have a LOT of spare time, I would even consider trying to implement the K-Means algorithm myself, because it's relevant to my interests!

### Some Resources to Look At!
Here are some resources I have found for this project: 
1. https://www.pyimagesearch.com/2014/07/07/color-quantization-opencv-using-k-means-clustering/
* Though this link is in python, procedurally, it is still relevant!

2. https://github.com/openframeworks/openFrameworks/tree/master/examples/video/asciiVideoExample
* This was a part of the open frameworks examples, and it accesses the webcam in a way similar to what I think I need to do for this project.

### How Can I Make This Project a Success? 
As long as I start early and do my research, this project should be a success :D
