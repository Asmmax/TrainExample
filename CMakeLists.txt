cmake_minimum_required (VERSION 3.8)

project ("TrainExample")

if (WIN32)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
endif()

add_subdirectory ("deps/dgnix")
add_subdirectory ("GUIApp")
