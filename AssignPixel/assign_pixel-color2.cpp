/* Based on OpenCV Documentation - Introduction → Fast Element Access section
 * Modified by Rafał Petryniak: http://sites.google.com/site/rafalpetryniakresearch/
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int, char**)
{
  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat img_frame, img_resultA, img_resultB, img_resultC;
  
  vector<Mat> planesA,planesB,planesC;
  
  const char *win_cam  = "Camera";
  const char *win_resA = "Result A";
  const char *win_resB = "Result B";
  const char *win_resC = "Result C";
  
  namedWindow(win_cam,  CV_WINDOW_AUTOSIZE);
  namedWindow(win_resA, CV_WINDOW_AUTOSIZE);
  namedWindow(win_resB, CV_WINDOW_AUTOSIZE);
  namedWindow(win_resC, CV_WINDOW_AUTOSIZE);
  
  while (cvWaitKey(4) == -1) {
    cap >> img_frame;
       
    // Method 1. process Y plane using an iterator
    
    split(img_frame, planesA); // split the image into separate color planes
    
    MatIterator_<uchar> 
      it1     = planesA[0].begin<uchar>(),
      it1_end = planesA[0].end<uchar>(),
      it2     = planesA[1].begin<uchar>(),
      it3     = planesA[2].begin<uchar>();
    
    for(; it1 != it1_end; ++it1,++it2,++it3 )
    {
      *it1 = 255 - *it1;
      *it2 = 255 - *it2;
      *it3 = 255 - *it3;
    }
    
    merge(planesA, img_resultA);
    
    // Method 2. process the first chroma plane using pre-stored row pointer.
    
    split(img_frame, planesB);
    
    for( int y = 0; y < img_frame.rows; y++ )
    {
      uchar* Uptr1 = planesB[0].ptr<uchar>(y);
      uchar* Uptr2 = planesB[1].ptr<uchar>(y);
      uchar* Uptr3 = planesB[2].ptr<uchar>(y);
      
      for( int x = 0; x < img_frame.cols; x++ )
      {
        Uptr1[x] = 255 - Uptr1[x];
        Uptr2[x] = 255 - Uptr2[x];
        Uptr3[x] = 255 - Uptr3[x];
      }
    }
    
    merge(planesB, img_resultB);
   
    // Method 3. process the second chroma plane using
    //           individual element access operations
    
    split(img_frame, planesC);
    
    for( int y = 0; y < img_frame.rows; y++ )
    {
      for( int x = 0; x < img_frame.cols; x++ )
      {
        uchar& Vxy1 = planesC[0].at<uchar>(y, x);
        uchar& Vxy2 = planesC[1].at<uchar>(y, x);
        uchar& Vxy3 = planesC[2].at<uchar>(y, x);
        
        Vxy1 = 255 - Vxy1;
        Vxy2 = 255 - Vxy2;
        Vxy3 = 255 - Vxy3;        
      }
    }
    
    merge(planesC, img_resultC);    
    
    imshow(win_cam,  img_frame);
    imshow(win_resA, img_resultA);
    imshow(win_resB, img_resultB);
    imshow(win_resC, img_resultC);
  }
  
  return 0;
}
