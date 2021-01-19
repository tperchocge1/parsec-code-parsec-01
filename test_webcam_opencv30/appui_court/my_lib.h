#ifndef MY_LIB_H
#define MY_LIB_H
#include <iostream>
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#include "opencv2/opencv.hpp"
#include <cuda_runtime.h>



using namespace std;
int texte(void){
cout << RED << "\n\n\n\n\n\n\n\n\nSelect Filtre \n"<<RESET;
cout <<YELLOW<<"\e[1m"<<"Filtre 1 Détection de contours \n"<<RESET;
cout<<MAGENTA<<"\e[1m"<<"Filtre 2 seuillage couleur rouge vers jaune\n"<<RESET;
cout<<CYAN<<"\e[1m"<<"Filtre 3 transformation en noir et blanc\n"<<RESET;
cout<<RED<<"Votre Choix      "<<RESET;
cout<<BLACK<<"Appuyer sur Echap pour sortir "<<RESET;
}
using namespace cv;
std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int contour(void)
{
 int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;

    std::string pipeline = gstreamer_pipeline(capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
	if(!cap.isOpened()) 
		return -1;
		while(1){

	    Mat frame,frame_out,frame_grayt;

	    cap >> frame;
	cvtColor(frame,frame_grayt,CV_BGR2GRAY);
	frame_out.create(frame.rows,frame.cols,CV_8UC1);
	    if (frame.empty())
	      break;

		for (int i=1;i<frame.rows;i++){
			for (int j=1;j<frame.cols;j++){
short temp;
				temp = (-1)*(short)frame_grayt.at<uchar>(i,j-1)+(-1)*(short)frame_grayt.at<uchar>(i-1,j)+(-1)*(char)frame_grayt.at<uchar>(i,j+1)+(-1)*(short)frame_grayt.at<uchar>(i+1,j)+4*(short)frame_grayt.at<uchar>(i,j);

frame_out.at<uchar>(i,j)=(uchar)abs(temp);

		if(frame_out.at<uchar>(i,j)>23) frame_out.at<uchar>(i,j)=255;
		else { frame_out.at<uchar>(i,j)=0;
			}			}		}
	    imshow( "Frame", frame_out );
	    char c=(char)waitKey(25);
	    if(c==27)
	      break;
	  }
	  cap.release();
	  destroyAllWindows();
	  return 0;
}

int seuillage(void)
{
 int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;

    std::string pipeline = gstreamer_pipeline(capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
	if(!cap.isOpened())  
		return -1;
float nr = 0;


	while(1){
	    Mat frame;
	    cap >> frame;
	    if (frame.empty())
	      break;

	for (int i=0;i<frame.rows;i++){
            for (int j=0;j<frame.cols;j++){
                uchar r,v,b;
                b=frame.at<Vec3b>(i,j)[0];
                v=frame.at<Vec3b>(i,j)[1];
                r=frame.at<Vec3b>(i,j)[2];
                nr=r/sqrt((r*r)+(b*b)+(v*v));
        if(nr>0.75)
            {
                frame.at<Vec3b>(i,j)[0]=0;
                frame.at<Vec3b>(i,j)[1]=r;
                frame.at<Vec3b>(i,j)[2]=r;
            }
        else{
            frame.at<Vec3b>(i,j)[0]=b;
            frame.at<Vec3b>(i,j)[1]=v;
            frame.at<Vec3b>(i,j)[2]=r;
        }
}
}
	    imshow( "Frame", frame );
	    char c=(char)waitKey(25);
	    if(c==27)
	      break;
	  }
	  cap.release();
	  destroyAllWindows();

	  return 0;
}

int blacknwhite(void)
{
 int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;
    std::string pipeline = gstreamer_pipeline(capture_width,
	capture_height,
	display_width,
	display_height,
	framerate,
	flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
	if(!cap.isOpened())  
		return -1;
float nr = 0;
	while(1){

	    Mat frame;
	    cap >> frame;
	    if (frame.empty())
	      break;

	for (int i=0;i<frame.rows;i++){
            for (int j=0;j<frame.cols;j++){
                uchar r,v,b;
                b=frame.at<Vec3b>(i,j)[0];
                v=frame.at<Vec3b>(i,j)[0];
                r=frame.at<Vec3b>(i,j)[0];
}
}
	    imshow( "Frame", frame );
	    char c=(char)waitKey(25);
	    if(c==27)
	      break;
	  }
	  cap.release();
	  destroyAllWindows();

	  return 0;
}


#endif
