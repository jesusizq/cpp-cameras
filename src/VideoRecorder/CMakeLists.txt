set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/VideoRecorder.cpp")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/VideoRecorder.hpp")

add_library("VideoRecorder" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("VideoRecorder" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
    VideoRecorder
    PRIVATE ${OpenCV_LIBS}
)
