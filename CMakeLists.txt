cmake_minimum_required(VERSION 2.8)
project( AdaptiveThresholding )
find_package( OpenCV REQUIRED )
include_directories(${OPENCV_INCLUDE_DIRS})
add_executable( AdaptiveThresholding AdaptiveThresholding.cpp )
target_link_libraries( AdaptiveThresholding ${OpenCV_LIBS} )
