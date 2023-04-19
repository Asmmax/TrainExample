cmake_minimum_required (VERSION 3.8)

set(guiapp_include_dir "include/")
set(guiapp_src_dir "src/")

file(GLOB_RECURSE guiapp_include "${guiapp_include_dir}/*.hpp")
file(GLOB_RECURSE guiapp_src "${guiapp_src_dir}/*.cpp")

add_executable (GUIApp 
${guiapp_include}
${guiapp_src} )

target_compile_features (GUIApp PRIVATE cxx_std_17)
target_include_directories(GUIApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GUIApp PRIVATE dgnix)

if(WIN32)
	set_target_properties(GUIApp PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()

set(RESOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.dat.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/settings.dat)
