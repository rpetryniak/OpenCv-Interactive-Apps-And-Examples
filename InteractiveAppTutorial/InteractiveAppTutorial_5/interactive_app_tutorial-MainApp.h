#ifndef MAINAPP_H
#define MAINAPP_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-Ball.h"

using namespace cv;

enum
{
  APP_MOUSE_LEFT   = 1,
  APP_MOUSE_RIGHT  = 2,
  APP_MOUSE_MIDDLE = 3,
};
void mouse_callback(int event, int x, int y, int flags, void* param);

//MainApp singelton class
class MainApp
{
private:
  Mat cam_frame, img_gray, img_first, img_prev, img_diff, img_bin;
  Mat canvas;               // Image for drawing
  Scalar bgr_color;         // Background color
  vector <Ball> myBall;
  bool pauseBallsMove;
  bool m_mousePressed;

public: // Some global params:
  static int DELAY;
  static int CANVAS_WIDTH;  
  static int CANVAS_HEIGHT;  
  static int INITIAL_BALLS_NUMBER;
  
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

  void keyPressed(int key);
  void mouseMoved(int mouseX, int mouseY );
  void mouseDragged(int mouseX, int mouseY);
  void mousePressed(int mouseX, int mouseY, int button);
  void mouseReleased(int mouseX, int mouseY, int button);
  void mouseDoubleClick(int mouseX, int mouseY, int button);
};

#endif
