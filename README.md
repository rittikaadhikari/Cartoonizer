# CS 126 FinalProject

## Cartoonizer
This application allows you to take selfies with your webcam in a multitude of filters, ranging from grayscale, redscreen, bluescreen, and emeraldscreen all the way to cartoonized and even illinify (if you want to show U of I pride ;)), all with popular background music. It also supports a real-time video cartoonizer, but this is currently in beta mode due to the slight lag and deprecation in quality.

My plan is to work on getting the application to work with threading in order to allow for a smoother and cleaner real-time cartoonizer.

## Motivation 
The main inspiration behind the Cartoonizer was early 2000s Apple PhotoBooth -- I fondly remember fooling around with the different filters pre-Snapchat and that's what inspired me to try and create different fun filters for my final project. 

## Build Status
In order to build this project, you need to make sure that you import the data folder in the bin in order to ensure that everything integrates properly. 

## Code Style
[![google](https://img.shields.io/badge/code%20style-standard-brightgreen.svg?style=flat)](https://google.github.io/styleguide/cppguide.html)
 
## Tech Used
<b>Built with</b>
- [openFrameworks](http://openframeworks.cc/)
- [openCv](https://opencv.org/)
- [ofSoundPlayer](http://openframeworks.cc/documentation/sound/ofSoundPlayer/)

## Installation
Simply run: <br>
```git clone https://github.com/uiuc-sp18-cs126/final-project-rittikaadhikari.git``` 
to clone the repository. 

Then use openFrameworks projectGenerator to import this application in the proper format.

Finally, make sure the data folder is located in the bin, call ```make run release``` and run the release to enjoy the Cartoonizer!

## Tests
I did not include any unit testing, as all parts of my application were much better suited to user testing than automated testing. 

## How to use?
All you need to do to use this application is various different key presses! For the filters, pose and click the button. It will then pause the screen, and all you need to do is press P or V to go back to normal video mode. 

Key Presses: 
- 'C' = Cartoonize 
- 'I' = Illinify 
- 'R' = RedScreen
- 'E' = EmeraldScreen
- 'B' = BlueScreen
- 'G' = GrayScale
- 'S' = ScreenGrab
- 'V' = Video Mode (also unpause) 
- 'P' = Pause (also unpause) 
- 'D' = Beta-Cartoonizer in Real-Time

## Credits
Helpful Resources: 
- [Posterizing using KMeans (Python)](https://www.pyimagesearch.com/2014/07/07/color-quantization-opencv-using-k-means-clustering/)
- [KMeans Clustering (C++)](https://docs.opencv.org/3.1.0/de/d63/kmeans_8cpp-example.html)
- [Play Sound](http://openframeworks.cc/documentation/sound/ofSoundPlayer/)
- [Grayscale (and Textures)](https://github.com/terrybu/videoGrabberOpenFrameworks)

Audio Credits (Booted using YoutubeToMP3 converter):
- [Ready for It, Taylor Swift](https://www.youtube.com/watch?v=T62maKYX9tU)
- [Havana, Camila Cabello](https://www.youtube.com/watch?v=HCjNJDNzw8Y)
- [Despacito, Luis Fonsi ft. Justin Bieber](https://www.youtube.com/watch?v=72UO0v5ESUo)


## License
© [Rittika Adhikari]
