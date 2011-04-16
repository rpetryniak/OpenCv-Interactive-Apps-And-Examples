#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int, char**)
{
  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat cam_frame, img_gray_v1, img_gray_v2, img_gray_v3;
  
  const char *win_cam     = "Camera";
  const char *win_gray_v1 = "Gray v1";
  const char *win_gray_v2 = "Gray v2";
  const char *win_gray_v3 = "Gray v3";
  
  namedWindow(win_cam,     CV_WINDOW_AUTOSIZE);
  namedWindow(win_gray_v1, CV_WINDOW_AUTOSIZE);
  namedWindow(win_gray_v2, CV_WINDOW_AUTOSIZE);
  namedWindow(win_gray_v3, CV_WINDOW_AUTOSIZE);
  
  while (cvWaitKey(4) == -1) {
    cap >> cam_frame;
    
    // Method 1: Old style method operating on data array
    cvtColor(cam_frame, img_gray_v1, CV_BGR2GRAY);
    
    for(int i = 0; i < img_gray_v1.rows; i++)
      for(int j = 0; j < img_gray_v1.cols; j++) {
        img_gray_v1.data[img_gray_v1.step*i + j] = 255 - img_gray_v1.data[img_gray_v1.step*i + j];
      }

    // Method 2: Assign pixel using .at() function
    cvtColor(cam_frame, img_gray_v2, CV_BGR2GRAY);
    
    for(int i = 0; i < img_gray_v2.rows; i++)
      for(int j = 0; j < img_gray_v2.cols; j++)
        img_gray_v2.at<uchar>(i,j) = 255 - img_gray_v2.at<uchar>(i,j);      
    
    // Method2: Use plain C operator []. More efficient than v1 
    //    if you need to process a whole row of a 2d array
    cvtColor(cam_frame, img_gray_v3, CV_BGR2GRAY);
    
    for(int i = 0; i < img_gray_v3.rows; i++)
    {
      uchar* img_gray_v3_i = img_gray_v3.ptr<uchar>(i);
      for(int j = 0; j < img_gray_v3.cols; j++)
        img_gray_v3_i[j] = 255 - img_gray_v3_i[j];
    }

    imshow(win_cam,     cam_frame);
    imshow(win_gray_v1, img_gray_v1);
    imshow(win_gray_v2, img_gray_v2);
    imshow(win_gray_v3, img_gray_v3);
  }
  
  return 0;
}
