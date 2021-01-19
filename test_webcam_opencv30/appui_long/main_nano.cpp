#include "opencv2/opencv.hpp"
#include "mylib.h"
using namespace cv;

std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
  
return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" + std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
		
}

int main(int, char**)
{ 
 int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;
    std::string pipeline = gstreamer_pipeline(capture_width,capture_height,display_width,display_height,framerate,flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";
	cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
	if(!cap.isOpened()) 
        return -1;
    while(1){
        	Mat frame;
		cap >> frame;   		
        		imshow( "Frame", frame);      
			char c=(char)waitKey(25);
	






			if(c=='1'){ //détection de contours 1
			Mat cont = contour(frame);
			imshow("contour", cont);
			}
			if(c=='2'){
			Mat bnw = blacknwhite(frame);//noir et blanc 2
			imshow("blacknwhite", bnw);
			}
                        if(c=='4'){
			Mat seuil = seuillage1(frame); //inversion de couleur 4
			imshow("seuillage", seuil);
			}
 			if(c=='r'){
			Mat seuil =  seuillage2(frame);// Filtre 2d Moyenne a
			imshow("seuillage", seuil);
			}
                        if(c=='z'){
			Mat seuil = seuillage3(frame);// Filtre 2d Median z
			imshow("seuillage", seuil);
			}
                        if(c=='e'){
			Mat seuil = seuillage4(frame);// Filtre 2d bilateral e
			imshow("seuillage", seuil);
			}
                        if(c=='c'){
			Mat seuil =mirroir(frame);// Filtre Mirroir
			imshow("seuillage", seuil);
			}			
			else if(c=='3'){
			Mat seuil = seuillage(frame);
			imshow("seuillage", seuil);//rouge vers jaune 3
			}									
        		if(c==27)
          		break;
      			}

  
    cap.release();
      destroyAllWindows();
      return 0;
}
