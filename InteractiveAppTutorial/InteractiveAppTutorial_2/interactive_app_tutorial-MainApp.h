#ifndef MAINAPP_H
#define MAINAPP_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-Ball.h"

using namespace cv;

//MainApp singelton class
class MainApp
{
private:
  Mat canvas;               // Image for drawing
  Scalar bgr_color;         // Background color
  Ball *myBall_1, *myBall_2, *myBall_3;
  
public: // Some global params:
  static int DELAY;
  static int CANVAS_WIDTH;  
  static int CANVAS_HEIGHT;  
  
private:
  MainApp() {}
  MainApp(const MainApp &);
  MainApp& operator=(const MainApp&);
  
  void setup();   // Initial commands for setup processing
  void update();  // Commands to modify the parameters
  void draw();    // Drawing functions:
  
public:
  static MainApp& getInstance()
  {
    static MainApp instance;
    return instance;
  }
  
  // Main loop function with displaying image support
  // and handle mouse and keyboard events
  void run();
};

#endif
