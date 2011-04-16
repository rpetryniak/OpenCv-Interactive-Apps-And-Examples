PROJECT(OpenCvInteractiveAppsAndExamples-AssignPixel)

cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE( OpenCV REQUIRED )

SET(SOURCES
  assign_pixel-color1
  assign_pixel-color2
  assign_pixel-color3
  assign_pixel-color4
  assign_pixel-gray
)

FOREACH(source ${SOURCES})
  ADD_EXECUTABLE(${source} ${source}.cpp)
  TARGET_LINK_LIBRARIES(${source} ${OpenCV_LIBS})
ENDFOREACH(source)
