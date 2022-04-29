cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MotionDetection VERSION 1.0.0 LANGUAGES CXX)
message(STATUS "Project: ${PROJECT_NAME} 1.0.0")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GSTREAMER_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GSTREAMER_VIDEO REQUIRED gstreamer-video-1.0)

find_package(OpenCV REQUIRED)
include_directories(
        ${GLIB_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
)
include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(
        ${GLIB_LIBRARY_DIRS}
        ${GSTREAMER_LIBRARY_DIRS}
)

link_directories(${GSTREAMER_LIBRARY_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})

add_subdirectory(src)
add_subdirectory(app)

# INSTALL TARGETS
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
