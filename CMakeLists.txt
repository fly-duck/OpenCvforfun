cmake_minimum_required(VERSION 2.8.3)

set(This OpenCvforfun)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


find_package(OpenCV REQUIRED)

enable_testing()
add_subdirectory(googletest)


#set output path 
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin") 


set(Headers include/CV.hpp)
set(Sources src/CV.cpp)



add_library(${This} STATIC ${Headers} ${Sources})


add_executable(video  ${Sources})
target_link_libraries (video ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})



