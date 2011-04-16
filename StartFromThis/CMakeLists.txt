PROJECT(OpenCvInteractiveAppsAndExamples-StartFromThis)

cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE( OpenCV REQUIRED )

SET(SOURCES
  camera-grab_frame1
  camera-grab_frame2
  intro_opencv
)

FOREACH(source ${SOURCES})
  ADD_EXECUTABLE(${source} ${source}.cpp)
  TARGET_LINK_LIBRARIES(${source} ${OpenCV_LIBS})
ENDFOREACH(source)
