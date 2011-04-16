/* Based on "Introduction" chapter from official OpenCV Documentation.
 * Modified by Rafał Petryniak: http://sites.google.com/site/rafalpetryniakresearch/
 */

//
// Simple retro-style photo effect done by adding noise to
// the luminance channel and reducing intensity of the chroma channels
//

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// all the new API is put into "cv" namespace. Export its content
using namespace cv;

int main( int argc, char** argv )
{
  VideoCapture cap(0);
  if( !cap.isOpened() ) return -1;
  
  Mat frame;
  
  const char *window = "OpenCV Intro Example";
  namedWindow(window, CV_WINDOW_AUTOSIZE);

  while (cvWaitKey(4) == -1) {
    cap >> frame;
  
    Mat img_yuv;
    // convert image to YUV color space.
    // The output image will be allocated automatically
    cvtColor(frame, img_yuv, CV_BGR2YCrCb); 
    
    // split the image into separate color planes
    vector<Mat> planes;
    split(img_yuv, planes);
    
    // another Mat constructor; allocates a matrix of the specified
    // size and type
    Mat noise(frame.size(), CV_8U);
    
    // fills the matrix with normally distributed random values;
    // there is also randu() for uniformly distributed random numbers. 
    // Scalar replaces CvScalar, Scalar::all() replaces cvScalarAll().
    randn(noise, Scalar::all(128), Scalar::all(20));
    
    // blur the noise a bit, kernel size is 3x3 and both sigma's 
    // are set to 0.5
    GaussianBlur(noise, noise, Size(3, 3), 0.5, 0.5);
    
    const double brightness_gain = 0;
    const double contrast_gain = 1.7;

    addWeighted(planes[0], contrast_gain, noise, 1, -128 + brightness_gain, planes[0]);

    const double color_scale = 0.5;
    // Mat::convertTo() replaces cvConvertScale.
    // One must explicitly specify the output matrix type
    // (we keep it intact, i.e. pass planes[1].type())
    planes[1].convertTo(planes[1], planes[1].type(), color_scale, 128*(1-color_scale));
    
    // alternative form of convertTo if we know the datatype
    // at compile time ("uchar" here).
    // This expression will not create any temporary arrays
    // and should be almost as fast as the above variant
    //planes[2] = Mat_<uchar>(planes[2]*color_scale + 128*(1-color_scale));
    planes[2].convertTo(planes[2], planes[2].type(), color_scale, 128*(1-color_scale));
    
    // Mat::mul replaces cvMul(). Again, no temporary arrays are
    // created in the case of simple expressions.
    planes[0] = planes[0].mul(planes[0], 1./255);
    
    // now merge the results back
    merge(planes, img_yuv);
    // and produce the output RGB image
    cvtColor(img_yuv, frame, CV_YCrCb2BGR);
    
    imshow(window, frame);
  }
    
  return 0;
  // all the memory will automatically be released
  // by vector<>, Mat and Ptr<> destructors.
}
