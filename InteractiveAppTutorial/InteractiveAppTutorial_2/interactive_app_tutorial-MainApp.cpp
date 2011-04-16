#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-MainApp.h"

using namespace cv;

// Best place to initialize global MainApp params:
int MainApp::DELAY        = 5;
int MainApp::CANVAS_WIDTH = 500;
int MainApp::CANVAS_HEIGHT= 350;

void MainApp::run() {
  setup();
  
  const char *win_canvas = "Canvas";
  namedWindow(win_canvas, CV_WINDOW_AUTOSIZE);
  
  while (cvWaitKey(4) == -1) {
    update();
    draw();
    
    imshow(win_canvas, canvas);
    waitKey(DELAY);
  }
}

void MainApp::setup() 
{
  bgr_color = Scalar(200,200,200);
  canvas = Mat(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3, bgr_color);
  
  myBall_1 = new Ball(&canvas);
  myBall_2 = new Ball(&canvas);
  myBall_3 = new Ball(&canvas);
}

void MainApp::draw() {
  canvas = bgr_color;
  
  myBall_1->draw();    
  myBall_2->draw();    
  myBall_3->draw();    
}

void MainApp::update() 
{
  myBall_1->update();
  myBall_2->update();
  myBall_3->update();
}

