#include "stdio.h"

#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "interactive_app_tutorial-MainApp.h"
#include "interactive_app_tutorial-util.h"

using namespace cv;

//--------------------------------------------------------------
// Best place to initialize global MainApp params:
int MainApp::DELAY        = 10;
int MainApp::CANVAS_WIDTH = 640;
int MainApp::CANVAS_HEIGHT= 480;
int MainApp::INITIAL_BALLS_NUMBER = 30;

//--------------------------------------------------------------
void MainApp::run() {
  setup();
  
  const char *win_canvas = "Canvas";
  namedWindow(win_canvas, CV_WINDOW_AUTOSIZE);
  cvSetMouseCallback(win_canvas, mouse_callback, this);

//start: Camera initialisation:
  
  CvCapture* camera = cvCreateCameraCapture(0);
  
  if (!camera) {
    printf("No capture device found!\n\n");
    exit(1);
  }
  // Try to set the camera resolution to 640 x 480.
  cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 640);
  cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 480);

  IplImage* frame = cvQueryFrame(camera);
  if(!frame) {
    printf("Caputuring error\n\n");
    exit(1);    
  }
  _cam_frame  = cvCreateMat(frame->height, frame->width, CV_8UC3);
  cvSetIdentity(_cam_frame);
    
  cvGetImage(_cam_frame, frame);
  cam_frame = cvarrToMat(_cam_frame);

  // Wait a little, so that the camera can auto-adjust its brightness.
  //sleep(1);    // (in seconds)
  
//stop: Camera initialisation:
  
  int   motionType      = 1; 
  int   motionThreshold = 20;
  float motionSigmaBlur = 2.0f;
  
  int key;
  bool first_frame = true;
  while(1) {
    key = cvWaitKey(DELAY);  // wait for keyboard input
    if (key == 'q') break;   // 'q' pressed, quit the program
    if (key != -1 ) keyPressed(key);

    IplImage* frame = cvQueryFrame(camera);
    if(!frame) break;

    cvGetImage(_cam_frame, frame);
    cam_frame = cvarrToMat(_cam_frame);
    
    flip(cam_frame,cam_frame,1);
    cvtColor(cam_frame, img_gray, CV_BGR2GRAY);
    GaussianBlur(img_gray, img_gray, Size(0,0), motionSigmaBlur, motionSigmaBlur);
    
    if (first_frame) {
      img_prev=img_gray.clone();
      first_frame = false;
      continue;
    }
    
    absdiff(img_gray, img_prev, img_diff);
    threshold(img_diff, img_bin, motionThreshold, 255, THRESH_BINARY);
    erode(img_bin,  img_bin, Mat(), Point(-1,-1), 3);
    dilate(img_bin, img_bin, Mat(), Point(-1,-1), 1);

    update();
    draw();
    
    imshow(win_canvas, canvas);
    
    if (motionType == 1) img_prev=img_gray.clone();
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
void MainApp::update() 
{
  int max_motion_points = 10;
  
  int movementAmount, ball_dim, ball_x, ball_y;
  int canvas_ind_x, canvas_ind_y;
  
  for (int k = 0; k < myBall.size(); k++) {
    movementAmount = 0;
    ball_dim = myBall[k].getDim();
    ball_x   = myBall[k].getX();
    ball_y   = myBall[k].getY();
    
    for (int i=(-1*ball_dim); i<ball_dim; i++)
      for (int j=(-1*ball_dim); j<ball_dim; j++)
        if ( dist(0,0,i,j) < ball_dim ) {          
          canvas_ind_x = ball_x + i;
          canvas_ind_y = ball_y + j;
          
          if ( canvas_ind_x<=0 || canvas_ind_y<=0 || canvas_ind_x>CANVAS_WIDTH || canvas_ind_y>CANVAS_HEIGHT) continue; 

          if ( img_bin.at<uchar>(canvas_ind_y,canvas_ind_x) > 30) {
            movementAmount++;
          }
        }
        
    if (movementAmount > max_motion_points)
      myBall[k].decrementLives();
    else
      if (!pauseBallsMove) myBall[k].update();
  }
  
  for(int i=0; i<myBall.size(); i++) {
    if(myBall[i].isEndLive()) {
      myBall.erase(myBall.begin()+i);
    }
  }
  
  if (myBall.size() == 0) {
    for (int i = 0; i < INITIAL_BALLS_NUMBER; i++){
      myBall.push_back( Ball(&canvas) );
    } 
  }
}

//--------------------------------------------------------------
void MainApp::draw() {
  //canvas = bgr_color;
  canvas = cam_frame;
  
  for (int i = 0; i < myBall.size(); i++){
    myBall[i].draw();
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


