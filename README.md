Simple C++ project for generating complex graphs/fractals

points "c" are colored based on their position c_n in the complex plane after n iterations of some complex function func().
The brightness is determined by c's distance from the origin, and its color is determined by theta. Both are calculated in Cmath.cpp Crgb().

![output](https://github.com/user-attachments/assets/e1d9a124-5802-41ec-bae8-05813872e632)
![mandelzoom](https://github.com/user-attachments/assets/3a6697da-d0b7-44d0-8dda-ccfa71552b45)
(made using ffmpeg bmp-sequence to gif, program only outputs bmp files, but animations can easily be made by iterating scale, position variables.)

for a more traditional coloring of fractals see the [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set), this should be possible to achieve with this project, only requiring a few changes to the Cmath.cpp Crgb() function. Might add that as a seperate function so toggling the coloring method is possible.
