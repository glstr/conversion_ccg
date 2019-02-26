project( bin )
cmake_minimum_required(VERSION 2.8.11)

# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )
  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  
endif()

# include helper file
include( ${CGAL_USE_FILE} )

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
