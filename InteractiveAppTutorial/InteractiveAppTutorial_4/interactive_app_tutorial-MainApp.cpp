#include "stdio.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-MainApp.h"

using namespace cv;

//--------------------------------------------------------------
// Best place to initialize global MainApp params:
int MainApp::DELAY        = 10;
int MainApp::CANVAS_WIDTH = 600;
int MainApp::CANVAS_HEIGHT= 500;
int MainApp::INITIAL_BALLS_NUMBER = 30;

//--------------------------------------------------------------
void MainApp::run() {
  setup();
  
  const char *win_canvas = "Canvas";
  namedWindow(win_canvas, CV_WINDOW_AUTOSIZE);
  cvSetMouseCallback(win_canvas, mouse_callback, this);

  int key;
  while(1) {
    key = cvWaitKey(DELAY);  // wait for keyboard input
    if (key == 'q') break;   // 'q' pressed, quit the program
    if (key != -1 ) keyPressed(key);

    update();
    draw();
    
    imshow(win_canvas, canvas);
  }
}

//--------------------------------------------------------------
void MainApp::setup() 
{
  pauseBallsMove = false;
  bgr_color = Scalar(200,200,200);
  canvas = Mat(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3, bgr_color);
  
  for (int i = 0; i < INITIAL_BALLS_NUMBER; i++){
    myBall.push_back( Ball(&canvas) );
  }
}

//--------------------------------------------------------------
void MainApp::draw() {
  canvas = bgr_color;
  
  for (int i = 0; i < myBall.size(); i++){
    myBall[i].draw();
  }  
}

//--------------------------------------------------------------
void MainApp::update() 
{
  if (!pauseBallsMove) {
    for (int i = 0; i < myBall.size(); i++) {
      myBall[i].update();
    }
  }
}

//--------------------------------------------------------------
void MainApp::keyPressed(int key){

  switch (key){
    case ' ':
      pauseBallsMove = !pauseBallsMove;
      break;
    case 'a':
      myBall.push_back( Ball(&canvas) );
      break;
    case 'd':
      if (myBall.size()>=1) myBall.pop_back();
      break;
  }
}

//--------------------------------------------------------------
void MainApp::mouseMoved(int mouseX, int mouseY ){
  if (m_mousePressed) mouseDragged(mouseX, mouseY);
}

//--------------------------------------------------------------
void MainApp::mouseDragged(int mouseX, int mouseY){
}

//--------------------------------------------------------------
void MainApp::mousePressed(int mouseX, int mouseY, int button){
  m_mousePressed = true;

  for(int i=0; i<myBall.size(); i++){
    if(myBall[i].checkMouseOver(mouseX, mouseY)){
      myBall[i].decrementLives();

      if(myBall[i].isEndLive()) myBall.erase(myBall.begin()+i);
    }
  }
}

//--------------------------------------------------------------
void MainApp::mouseReleased(int mouseX, int mouseY, int button){
  m_mousePressed = false;
}

//--------------------------------------------------------------
void MainApp::mouseDoubleClick(int mouseX, int mouseY, int button){
}

//--------------------------------------------------------------

void mouse_callback(int event, int x, int y, int flags, void* param)
{
  MainApp *app = ((MainApp *)param);
  switch (event) {
    case  CV_EVENT_LBUTTONDBLCLK:
      app->mouseDoubleClick(x,y,APP_MOUSE_LEFT);   break;
    case  CV_EVENT_RBUTTONDBLCLK:
      app->mouseDoubleClick(x,y,APP_MOUSE_RIGHT);  break;
    case  CV_EVENT_MBUTTONDBLCLK:
      app->mouseDoubleClick(x,y,APP_MOUSE_MIDDLE); break;
    case  CV_EVENT_LBUTTONDOWN:
      app->mousePressed(x,y,APP_MOUSE_LEFT);       break;
    case  CV_EVENT_RBUTTONDOWN:
      app->mousePressed(x,y,APP_MOUSE_RIGHT);      break;
    case  CV_EVENT_MBUTTONDOWN:
      app->mousePressed(x,y,APP_MOUSE_MIDDLE);     break;
    case  CV_EVENT_LBUTTONUP:
      app->mouseReleased(x,y,APP_MOUSE_LEFT);      break;
    case  CV_EVENT_RBUTTONUP:
      app->mouseReleased(x,y,APP_MOUSE_RIGHT);     break;
    case  CV_EVENT_MBUTTONUP:
      app->mouseReleased(x,y,APP_MOUSE_MIDDLE);    break;
    case  CV_EVENT_MOUSEMOVE:
      app->mouseMoved(x,y);                        break;
  }
}


