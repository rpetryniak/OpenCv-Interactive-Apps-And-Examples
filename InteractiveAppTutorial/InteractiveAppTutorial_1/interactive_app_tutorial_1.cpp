#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

//MainApp singelton class
class MainApp
{
private:
  Mat canvas;               // Image for drawing
  Scalar bgr_color;         // Background color
  int x, y, speedX, speedY; // Circle local params
  
public: // Some global params:
  static int DELAY;
  static int CANVAS_WIDTH;  
  static int CANVAS_HEIGHT;  
  
private:
  MainApp() {}
  MainApp(const MainApp &);
  MainApp& operator=(const MainApp&);
  
  // Initial commands for setup processing
  void setup() 
  {
    x = 0;
    y = 0;
    speedX = 1;
    speedY = 1;
    
    bgr_color = Scalar(120,235,139);
    canvas = Mat(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3, bgr_color);
  }
  
  // Commands to modify the parameters
  void update() 
  {
    if(x < 0 ){
      x = 0;
      speedX *= -1;
    } else if(x > CANVAS_WIDTH){
      x = CANVAS_WIDTH;
      speedX *= -1;
    }
    
    if(y < 0 ){
      y = 0;
      speedY *= -1;
    } else if(y > CANVAS_HEIGHT){
      y = CANVAS_HEIGHT;
      speedY *= -1;
    } 
    
    x+=speedX;
    y+=speedY;    
  }
  
  // Drawing functions:
  void draw() {
    canvas = bgr_color;
    circle(canvas, Point(x,y), 30, Scalar(0,255,255),-1,CV_AA);
  }
  
public:
  static MainApp& getInstance()
  {
    static MainApp instance;
    return instance;
  }
  
  // Main loop function with displaying image support
  // and handle mouse and keyboard events
  void run() {
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
};

// Best place to initialize global MainApp params:
int MainApp::DELAY        = 5;
int MainApp::CANVAS_WIDTH = 500;
int MainApp::CANVAS_HEIGHT= 350;

int main(int, char**)
{
  MainApp::getInstance().run();
  
  return 0;
}

