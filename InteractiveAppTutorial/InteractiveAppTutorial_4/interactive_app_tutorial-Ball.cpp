#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-Ball.h"
#include "interactive_app_tutorial-MainApp.h"
#include "interactive_app_tutorial-util.h"

using namespace cv;

extern RNG rng;

void Ball::setup()
{
  x = rng.uniform(0, MainApp::CANVAS_WIDTH);       // give some random positioning
  y = rng.uniform(0, MainApp::CANVAS_HEIGHT);
  speedX = rng.uniform((float)-2, (float)2);   // and random speed and direction
  speedY = rng.uniform((float)-2, (float)2);
  dim    = rng.uniform(20,60);
  
  color = randomColor(rng);
  lives = 3;
}

void Ball::update() 
{
  if(x < 0 ){
    x = 0;
    speedX *= -1;
  } else if(x > MainApp::CANVAS_WIDTH){
    x = MainApp::CANVAS_WIDTH;
    speedX *= -1;
  }
  
  if(y < 0 ){
    y = 0;
    speedY *= -1;
  } else if(y > MainApp::CANVAS_HEIGHT){
    y = MainApp::CANVAS_HEIGHT;
    speedY *= -1;
  } 
  
  x+=speedX;
  y+=speedY;  
}

void Ball::draw()
{
  circle(*canvas, Point(x,y), dim, color,-1,CV_AA); 
  putText( *canvas, toString(lives), cvPoint(x,y),CV_FONT_HERSHEY_SIMPLEX,0.5f,CV_RGB(255,255,255));
}

bool Ball::checkMouseOver(int _mouseX, int _mouseY) {
  bool mouseIsOver = false;

  if ( dist(_mouseX,_mouseY,x,y) < dim ) mouseIsOver = true;

  return mouseIsOver;
}

void Ball::decrementLives() {
  lives--;
}

bool Ball::isEndLive() {
  return (lives <= 0);
}
