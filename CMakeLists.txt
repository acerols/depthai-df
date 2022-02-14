cmake_minimum_required(VERSION 3.2)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/depthai-core EXCLUDE_FROM_ALL)

set(RECODER depthai_command_recorder)
project(${RECODER})

find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable("${RECODER}"
    src/${RECODER}/main.cpp
)

target_link_libraries(${RECODER}
    PUBLIC
        depthai::opencv
        Qt5::Widgets
        ${OpenCV_LIBS} # optional, used for example
)

if(NOT MSVC)
    target_compile_options(${RECODER} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Werror=return-type>)
endif()


set_property(TARGET ${RECODER} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${RECODER} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${RECODER} PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET ${RECODER} PROPERTY CMAKE_AUTOMOC ON)
set_property(TARGET ${RECODER} PROPERTY CMAKE_AUTORCC ON)
set_property(TARGET ${RECODER} PROPERTY CMAKE_AUTOUIC ON)


