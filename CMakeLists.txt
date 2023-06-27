cmake_minimum_required(VERSION 3.10)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x86-windows/share/opencv2")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(my_project main.cpp)

target_link_libraries(my_project ${OpenCV_LIBS})
