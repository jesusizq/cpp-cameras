set(APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    MotionRecorderApp
    CameraConnector
    GStreamerPipeline
    MotionDetector
    VideoRecorder
    Logger
    FrameQueue
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
