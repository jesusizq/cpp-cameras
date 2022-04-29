set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GStreamerPipeline.cpp")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GStreamerPipeline.hpp")

add_library("GStreamerPipeline" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("GStreamerPipeline" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    GStreamerPipeline
    PRIVATE ${GSTREAMER_LIBRARIES}
)
