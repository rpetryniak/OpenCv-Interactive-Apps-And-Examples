#ifndef BALL_H
#define BALL_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

//Ball class
class Ball 
{
private:
  Mat *canvas;
  float x, y, dim;
  float speedX, speedY;
  Scalar color;
  
  Ball();
  void setup();
  
public:
  Ball(Mat *can)
  {
    canvas = can;
    setup();
  }
  
  void update();
  void draw();
};

#endif
