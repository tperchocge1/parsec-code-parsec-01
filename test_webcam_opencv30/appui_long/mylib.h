
#ifndef MYLIB_H 
#define MYLIB_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdlib.h>



using namespace cv;
Mat contour (Mat frame);
Mat seuillage(Mat frame);
Mat seuillage1(Mat frame);
Mat seuillage2(Mat frame);
Mat seuillage3(Mat frame);
Mat seuillage4(Mat frame);
Mat mirroir(Mat frame);
Mat blacknwhite( Mat frame);





#endif
