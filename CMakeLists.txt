cmake_minimum_required(VERSION 2.8)

PROJECT(CylinderRenderingProperties)

find_package(VTK REQUIRED)
find_package(gflags REQUIRED)
include(${VTK_USE_FILE})

add_executable(main MACOSX_BUNDLE src/delaunay.cpp src/renderwin.cpp  src/fileconv.cpp src/common_flag.cpp src/main.cpp)
target_link_libraries(main ${VTK_LIBRARIES} gflags)
