#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int, char**)
{
  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat frame, result;

  const char *win_cam = "Camera";
  const char *win_res = "Result";
  
  namedWindow(win_cam, CV_WINDOW_AUTOSIZE);
  namedWindow(win_res, CV_WINDOW_AUTOSIZE);
  
  int i,j,k;
  int channels = 3;
  
  while (cvWaitKey(4) == -1) {
    cap >> frame;
    
    result = frame.clone();

    // invert the image
    for(i=0;i<frame.rows;i++) 
      for(j=0;j<frame.cols;j++) 
        for(k=0;k<channels;k++) {

          uchar* temp_ptr = &((uchar*)(result.data + result.step*i))[j*3];
          temp_ptr[0] = 255 - temp_ptr[0];
          temp_ptr[1] = 255 - temp_ptr[1];
          temp_ptr[2] = 255 - temp_ptr[2];    
        }
        
    imshow(win_cam, frame);
    imshow(win_res, result);
  }
  
  return 0;
}
