cmake_minimum_required (VERSION 3.8)

set(guiapp_include_dir "include/")
set(guiapp_src_dir "src/")

set(out_include_path "${PROJECT_BINARY_DIR}/.generated/GUIApp/${guiapp_include_dir}")
set(out_source_path "${PROJECT_BINARY_DIR}/.generated/GUIApp/${guiapp_src_dir}")
set(cache_path "${PROJECT_BINARY_DIR}/.generated/GUIApp")
set(scripts_dir "${PROJECT_SOURCE_DIR}/scripts")

if (WIN32)
	message (STATUS "Generating containers for Current")
	get_target_property(add_includes glm_interface INTERFACE_INCLUDE_DIRECTORIES)
	list(GET add_includes 0 add_include)
	set(in_path "${CMAKE_CURRENT_SOURCE_DIR}/${guiapp_include_dir}")
	set(gen_dir "GUIApp")
	execute_process(
		COMMAND cmd /C set out_include_dir=${gen_dir} && set out_source_dir=${gen_dir} && set add_includes=${add_include} && set cache_path=${cache_path} && call "${scripts_dir}/win/generate_containers.bat" ${in_path} ${out_include_path} ${out_source_path}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
endif()

file(GLOB_RECURSE guiapp_include "${guiapp_include_dir}/*.hpp")
file(GLOB_RECURSE guiapp_src "${guiapp_src_dir}/*.cpp")

file(GLOB_RECURSE gen_include 
"${out_include_path}/*.hpp")

file(GLOB_RECURSE gen_src 
"${out_source_path}/*.cpp")

add_executable (GUIApp 
${guiapp_include}
${guiapp_src}
${gen_include}
${gen_src})

target_compile_features (GUIApp PRIVATE cxx_std_17)
target_include_directories(GUIApp 
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
PRIVATE "${out_include_path}")

target_link_libraries(GUIApp PRIVATE dgnix PRIVATE DIAssets)

if(WIN32)
	set_target_properties(GUIApp PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()

set(RESOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.dat.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/settings.dat)
