PROJECT(OpenCvInteractiveAppsAndExamples-InteractiveAppTutorial3)

cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE( OpenCV REQUIRED )

ADD_EXECUTABLE(interactive_app_tutorial_3 interactive_app_tutorial-main.cpp interactive_app_tutorial-MainApp.cpp interactive_app_tutorial-Ball.cpp)
TARGET_LINK_LIBRARIES(interactive_app_tutorial_3 ${OpenCV_LIBS})
