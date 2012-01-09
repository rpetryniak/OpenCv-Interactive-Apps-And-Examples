#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-MainApp.h"

using namespace cv;

RNG rng(cvGetTickCount());

int main(int, char**)
{
  MainApp::getInstance().run();
  
  return 0;
}

