cmake_minimum_required(VERSION 2.8)

PROJECT(CylinderRenderingProperties)

find_package(VTK REQUIRED)
find_package(gflags REQUIRED)
include(${VTK_USE_FILE})

#find_package(PCL 1.3 REQUIRED COMPONENTS common io)
find_package(PCL 1.6 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(main MACOSX_BUNDLE src/delaunay.cpp src/renderwin.cpp  src/fileconv.cpp src/common_flag.cpp src/main.cpp)
target_link_libraries(main ${VTK_LIBRARIES} gflags ${PCL_LIBRARIES})
