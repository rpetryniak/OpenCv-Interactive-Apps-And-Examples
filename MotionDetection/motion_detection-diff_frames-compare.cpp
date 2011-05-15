#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../include/myFunction.h"

using namespace cv;

int main(int argc, char** argv)
{
  const char * _thresval = getCmdOption("-thr",    "30", argc, argv);
  const char * _sigma    = getCmdOption("-gblur", "2.0", argc, argv);

  int thresval = atoi( _thresval );
  float sigma  = atof(_sigma);

  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat cam_frame, img_gray, img_first, img_prev, img_diff, img_bin;

  const char *win_diff1 = "Diff from first frame"; namedWindow(win_diff1, CV_WINDOW_AUTOSIZE);
  const char *win_diff2 = "Diff from prev frame";  namedWindow(win_diff2, CV_WINDOW_AUTOSIZE);

  bool first_frame = true;
  while (cvWaitKey(4) == -1) {
    cap >> cam_frame;

    flip(cam_frame,cam_frame,1);
    cvtColor(cam_frame, img_gray, CV_BGR2GRAY);
    GaussianBlur(img_gray, img_gray, Size(0,0), sigma, sigma);
    
    if (first_frame) {
        img_prev  = img_gray.clone();
        img_first = img_gray.clone();
        first_frame = false;
        continue;
    }

    absdiff(img_gray, img_prev, img_diff);
    threshold(img_diff, img_bin, thresval, 255, THRESH_BINARY);
    erode(img_bin,  img_bin, Mat(), Point(-1,-1), 3);
    dilate(img_bin, img_bin, Mat(), Point(-1,-1), 1);
    imshow(win_diff1, img_bin);

    absdiff(img_gray, img_first, img_diff);
    threshold(img_diff, img_bin, thresval, 255, THRESH_BINARY);
    erode(img_bin,  img_bin, Mat(), Point(-1,-1), 3);
    dilate(img_bin, img_bin, Mat(), Point(-1,-1), 1);
    imshow(win_diff2, img_bin);

    img_prev=img_gray.clone();
    
    waitKey(50);
  }
  
  return 0;
}
