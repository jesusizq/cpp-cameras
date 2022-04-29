set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/CameraConnector.cpp")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/CameraConnector.hpp")

add_library("CameraConnector" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("CameraConnector" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
    CameraConnector
    PRIVATE ${OpenCV_LIBS})
