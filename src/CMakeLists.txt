project( bin )
cmake_minimum_required(VERSION 2.8.11)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} CGAL_USE_BASIC_VIEWER")

# CGAL and its components
#find_package( CGAL QUIET COMPONENTS )

find_package(CGAL COMPONENTS Qt5 Core)

include(${CGAL_USE_FILE})

find_package(Qt5 QUIET COMPONENTS Xml Script OpenGL Svg)

#include_directories (BEFORE ../../include)
#if ( NOT Qt5_FOUND ) 
#    message("qt5 not found")
#    return()
#endif()

#if ( NOT CGAL_Qt5_FOUND )
#    message("cgal qt5 not found")
#    return()
#endif()

#if ( CGAL_FOUND AND CGAL_Qt5_FOUND AND Qt5_FOUND )
if ( CGAL_FOUND )
  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
  add_definitions(-DQT_NO_KEYWORDS)
  if( CGAL_Core_FOUND)
    add_definitions(-DCGAL_USE_CORE)
    endif()
else()
    message("qt not found")
    return()
endif()

#if ( NOT CGAL_FOUND )
#  message(STATUS "This project requires the CGAL library, and will not be compiled.")
#  return()  
#else() 
#  add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
#endif()

# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )
  message(STATUS "This project requires the Boost library, and will not be compiled.")
  return()  
endif()

# include for local directory

# include for local package
include_directories( BEFORE ../include )

find_package(VTK REQUIRED)
find_package(gflags REQUIRED)
include(${VTK_USE_FILE})

#find_package(PCL 1.3 REQUIRED COMPONENTS common io)
find_package(PCL 1.6 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Creating entries for all C++ files with "main" routine
# ##########################################################
include( CGAL_CreateSingleSourceCGALProgram )

aux_source_directory(. SRC_LIST)
add_executable(main ${SRC_LIST})
target_link_libraries(main ${VTK_LIBRARIES} gflags ${PCL_LIBRARIES})
