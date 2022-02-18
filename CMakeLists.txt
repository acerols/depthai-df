cmake_minimum_required(VERSION 3.2)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/depthai-core EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/mono)

set(RECODER depthai_command_recorder)
project(${RECODER})

find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable("${RECODER}"
    src/${RECODER}/main.cpp
    src/gui.cpp
)

target_include_directories(${RECODER} PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    ${Qt5_INCLUDE_DIRS}
    ./mono/include
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(${RECODER}
    PUBLIC
        depthai::core
        Qt5::Widgets
        ${OpenCV_LIBS} # optional, used for example
    mono
)


set_property(TARGET ${RECODER} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${RECODER} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${RECODER} PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET ${RECODER} PROPERTY CMAKE_AUTOMOC ON)
set_property(TARGET ${RECODER} PROPERTY CMAKE_AUTORCC ON)
set_property(TARGET ${RECODER} PROPERTY CMAKE_AUTOUIC ON)


