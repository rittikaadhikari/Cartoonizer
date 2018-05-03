# Development: Cartoonizer

## WEEK 1: 
This week, I worked on trying to get the ofVideoGrabber working like it did in the Ascii openframeworks example. After getting 
that, I started working on using opencv in order to get the K-Means color quantization working. My biggest hurdle of the week
was definitely spent in just trying to IMPORT opencv, and then trying to understand the documentation. 

At this point, I have a black screen (though my actual video grabbing functionality works), and it seems to lag immensely whenever
I try to run the K-Means algorithm. 

## WEEK 2: 
This week, I worked on getting opencv's K-Means algorithm working. This in itself was a challenge, because the pixels weren't updating
as expected, and K-Means wasn't working on non-black-and-white pixels. As of now, I have the cartoonizer up and running, though
it does have a little bit of lag, it's not as bad as before. 

I'm going to try and experiment with the parameters to see if I can get the cartoonizer to work in different hues and to see if I 
can make a clearer picture.

## WEEK 3: 
This week, I worked on adding the final touches to my project. Since the cartoonizer is kind of laggy, my code moderator and I decided that it might be better to leave the actual video-to-cartoon conversion as a beta mode, and work on cartoonizing an image. 

Surprisingly, a majority of my time was spent trying to figure out how to actually get the video to show up in the correct hues on the screen. Turns out, you have to call draw on the texture, not on the video in order to get the correct pixels to show up. Additionally, it took a while for me to try and figure out how to save images WITH the filters, because even though the filters were showing up on the screen, they were saving as plain images. I fixed this by saving the pixel-version of the texture, instead of grabbing the video and saving that. 

Finally, my last challenge was definitely figuring out how to get red-screen, green-screen, blue-screen, and illinify to work, because the pixels accepted by ofTexture were of type unsigned char. I had no idea how to get this conversion from pixel to character, but after a lot of digging in the documentation, I found that ofTexture can load data directly from image pixels, so I made a temp white image, assigned the according pixels, and then created my texture that way. 
