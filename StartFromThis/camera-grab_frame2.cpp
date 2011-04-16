#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int, char**)
{
  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat frame;
  Mat_<Vec3b> rgb;
  
  const char *window = "Example 2";
  namedWindow(window, CV_WINDOW_AUTOSIZE);
  const char *window2 = "rgb";
  namedWindow(window2, CV_WINDOW_AUTOSIZE);
  
  
  while (cvWaitKey(4) == -1) {
    cap >> frame;
    
    cvtColor(frame, rgb, CV_BGR2RGB);
    
    for(int i = 0; i < rgb.rows; i++)
      for(int j = 0; j < rgb.cols; j++)
        for(int k = 0; k < 3; k++)
          rgb(i,j)[k] = 255 - rgb(i,j)[k];
    
    imshow(window, frame);
    imshow(window2, rgb);
  }
  
  return 0;
}
