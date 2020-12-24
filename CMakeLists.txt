cmake_minimum_required(VERSION 3.5)

project(gaDigitalTransfo)


# include eigen
find_package(Eigen3 REQUIRED)


if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()

find_package(OpenCV REQUIRED)
if(${OpenCV_FOUND})
    message(STATUS "lib opencv found")
    message(STATUS “OpenCV version: ${OpenCV_VERSION}”)
    message(STATUS “OpenCV include dirs: ”)
    foreach(opencvIncludeDirs ${OpenCV_INCLUDE_DIRS})
        message(STATUS ${opencvIncludeDirs})
    endforeach()

    foreach(opencvLibs ${OpenCV_LIBS})
        message(STATUS ${opencvLibs})
    endforeach()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# check opencv version
if(${OpenCV_VERSION} VERSION_LESS 3.0.0)
    foreach(opencvLibs ${OpenCV_LIBS})
        message(STATUS ${opencvLibs})
    endforeach()
    message(FATAL_ERROR “OpenCV version is not compatible : ${OpenCV_VERSION}”)
endif()



# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O2 -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

# files to compile
file(GLOB_RECURSE source_files src/*.cpp include/*.h)
message(STATUS "  files " ${source_files})

# compile
add_executable(gaDigitalTransfo ${source_files} include/GADigitizedRotation.h include/GAPixelTransformation.h)

# link libs
include_directories(${EIGEN3_INCLUDE_DIR}
gaLib/
include/)

target_link_libraries(gaDigitalTransfo ${OpenCV_LIBS})