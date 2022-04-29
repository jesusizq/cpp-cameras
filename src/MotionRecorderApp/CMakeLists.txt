set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MotionRecorderApp.cpp")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/MotionRecorderApp.hpp")

add_library("MotionRecorderApp" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("MotionRecorderApp" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    MotionRecorderApp
    PRIVATE VideoRecorder
            CameraConnector
            GStreamerPipeline
            MotionDetector
            Logger
            FrameQueue
)
