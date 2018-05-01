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
