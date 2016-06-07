cmake_minimum_required(VERSION 3.5)
project(Hough_Transform_OCR_Image)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp src/DetectEdge.h src/DetectEdge.cpp src/HoughDetectEdge.cpp src/HoughDetectEdge.h src/Tools.cpp src/Tools.h src/LSDDetectEdge.cpp src/LSDDetectEdge.h)

add_executable(Hough_Transform_OCR_Image ${SOURCE_FILES})

target_link_libraries(Hough_Transform_OCR_Image ${OpenCV_LIBS})