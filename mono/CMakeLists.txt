cmake_minimum_required(VERSION 3.2)

set(MONO mono)
project(${MONO})

find_package(OpenCV REQUIRED)

add_library(${MONO}
    STATIC ./src/monocam.cc
)

target_include_directories(${MONO} INTERFACE
    ${OPENCV_INCLUDE_DIRS}
    ./includ/
    ./mono/include/
)

target_link_libraries(${MONO}
    PUBLIC
        depthai::core
        depthai::opencv
        ${OpenCV_LIBS} # optional, used for example
)


set_property(TARGET ${MONO} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${MONO} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${MONO} PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET ${MONO} PROPERTY CMAKE_AUTOMOC ON)
set_property(TARGET ${MONO} PROPERTY CMAKE_AUTORCC ON)
set_property(TARGET ${MONO} PROPERTY CMAKE_AUTOUIC ON)


