#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../include/myFunction.h"

using namespace cv;

int main(int argc, char** argv)
{
  const char * _diffType = getCmdOption("-type",  "2", argc, argv);
  const char * _thresval = getCmdOption("-thr",  "60", argc, argv);

  int diffType = atoi( _diffType );
  int thresval = atoi( _thresval );

  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat cam_frame, img_gray, img_prev, img_diff, img_bin;

  const char *win_cam  = "Camera input";      namedWindow(win_cam,  CV_WINDOW_AUTOSIZE);
  const char *win_gray = "Gray image";        namedWindow(win_gray, CV_WINDOW_AUTOSIZE);
  const char *win_diff = "Binary diff image"; namedWindow(win_diff, CV_WINDOW_AUTOSIZE);
    
  bool first_frame = true;
  while (cvWaitKey(4) == -1) {
    cap >> cam_frame;
    cvtColor(cam_frame, img_gray, CV_BGR2GRAY);
    
    if (first_frame) {
        img_prev=img_gray.clone();
        first_frame = false;
        continue;
    }

    absdiff(img_gray, img_prev, img_diff);
    threshold(img_diff, img_bin, thresval, 255, THRESH_BINARY);
    erode(img_bin,  img_bin, Mat(), Point(-1,-1), 3);
    dilate(img_bin, img_bin, Mat(), Point(-1,-1), 1);

    imshow(win_cam,  cam_frame);
    imshow(win_gray, img_gray);
    imshow(win_diff, img_bin);
    
    if (diffType == 1) img_prev=img_gray.clone();
  }
  
  return 0;
}
