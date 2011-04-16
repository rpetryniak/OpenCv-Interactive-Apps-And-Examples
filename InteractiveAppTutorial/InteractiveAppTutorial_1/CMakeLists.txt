PROJECT(OpenCvInteractiveAppsAndExamples-InteractiveAppTutorial1)

cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE( OpenCV REQUIRED )

SET(SOURCES
  interactive_app_tutorial_1
)

FOREACH(source ${SOURCES})
  ADD_EXECUTABLE(${source} ${source}.cpp)
  TARGET_LINK_LIBRARIES(${source} ${OpenCV_LIBS})
ENDFOREACH(source)
