PROJECT(OpenCvInteractiveAppsAndExamples-MotionDetection)

cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE( OpenCV REQUIRED )

SET(SOURCES
  motion_detection-diff_frames
  motion_detection-diff_frames-compare
)

FOREACH(source ${SOURCES})
  ADD_EXECUTABLE(${source} ${source}.cpp)
  TARGET_LINK_LIBRARIES(${source} ${OpenCV_LIBS})
ENDFOREACH(source)
