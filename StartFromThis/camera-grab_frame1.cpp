#include "opencv/highgui.h"

int main() 
{
  // Get an OpenCV camera handle
  CvCapture *cam = cvCaptureFromCAM(-1);
  
  // Initialise the GUI
  const char *window = "Example 1";
  cvNamedWindow(window, CV_WINDOW_AUTOSIZE);
  
  // The main loop
  while (cvWaitKey(4) == -1) {
    IplImage *frame = cvQueryFrame(cam);
    cvShowImage(window, frame);
  }
  
  // Clean up
  cvDestroyAllWindows();
  cvReleaseCapture(&cam);
  
  return 0;
}

/* 
Compilation:
  gcc camera1.cpp -o camera1 -lhighgui
 
Usage:
  ./camera1
*/
