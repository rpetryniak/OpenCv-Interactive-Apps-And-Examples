#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int, char**)
{
  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat frame;
  
  const char *window = "Example 2";
  namedWindow(window, CV_WINDOW_AUTOSIZE);
  
  while (cvWaitKey(4) == -1) {
    cap >> frame;
    
    Mat_<Vec3b>& frame_ = (Mat_<Vec3b>&)frame;

    for(int i = 0; i < frame_.rows; i++)
      for(int j = 0; j < frame_.cols; j++)
        for(int k = 0; k < 3; k++)
          frame_(i,j)[k] = 255 - frame_(i,j)[k];
    
    imshow(window, frame_);
  }
  
  return 0;
}
