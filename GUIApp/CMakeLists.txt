cmake_minimum_required (VERSION 3.8)

function(get_link_libraries OUTPUT_LIST TARGET)
    list(APPEND VISITED_TARGETS ${TARGET})
    get_target_property(LIBS ${TARGET} INTERFACE_LINK_LIBRARIES)
    set(ALL_LIBS "")
    foreach(LIB ${LIBS})
        if (TARGET ${LIB})
            list(FIND VISITED_TARGETS ${LIB} VISITED)
            if (${VISITED} EQUAL -1)
                get_link_libraries(LINK_LIBS ${LIB})
                list(APPEND ALL_LIBS ${LIB} ${LINK_LIBS})
            endif()
        endif()
    endforeach()
    set(VISITED_TARGETS ${VISITED_TARGETS} PARENT_SCOPE)
    set(${OUTPUT_LIST} ${ALL_LIBS} PARENT_SCOPE)
endfunction()

function(get_include_directories OUTPUT_LIST TARGET)
    get_target_property(ALL_INCLUDES ${TARGET} INTERFACE_INCLUDE_DIRECTORIES)
    set(LIBS)
    get_link_libraries(LIBS ${TARGET})
	foreach(LIB ${LIBS})
        if (TARGET ${LIB})
            set(LIB_INCLUDES)
            get_target_property(LIB_INCLUDES ${LIB} INTERFACE_INCLUDE_DIRECTORIES)
            list(APPEND ALL_INCLUDES ${LIB_INCLUDES})
        endif()
    endforeach()
	set(${OUTPUT_LIST} ${ALL_INCLUDES} PARENT_SCOPE)
endfunction()

set(guiapp_include_dir "include/")
set(guiapp_src_dir "src/")
set(assets_dir "${CMAKE_CURRENT_SOURCE_DIR}/assets")

set(out_include_path "${PROJECT_BINARY_DIR}/.generated/GUIApp/${guiapp_include_dir}")
set(out_source_path "${PROJECT_BINARY_DIR}/.generated/GUIApp/${guiapp_src_dir}")
set(cache_path "${PROJECT_BINARY_DIR}/.generated/GUIApp")
set(scripts_dir "${PROJECT_SOURCE_DIR}/scripts")

find_package (Python3 COMPONENTS Interpreter)

if (NOT Python3_FOUND AND NOT Python3_Interpreter_FOUND)
    message( FATAL_ERROR "You need python3 to generate some projects files!" )
endif()

if (NOT EXISTS ${PROJECT_SOURCE_DIR}/.venv)
    message (STATUS "Installing python env")
    execute_process(
		COMMAND ${Python3_EXECUTABLE} -m venv .venv
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		)
endif()

if (WIN32)
    set(Python3_ENV ${PROJECT_SOURCE_DIR}/.venv/Scripts)
else()
    set(Python3_ENV ${PROJECT_SOURCE_DIR}/.venv/bin)
endif()

execute_process(
    COMMAND ${Python3_ENV}/python -m pip show libclang
    RESULT_VARIABLE LIBCLANG_EXISTS
    OUTPUT_QUIET
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

if (NOT ${LIBCLANG_EXISTS} EQUAL 0)
    message (STATUS "Installing libclang package")
    execute_process(
        COMMAND ${Python3_ENV}/python -m pip install wheel
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
    execute_process(
        COMMAND ${Python3_ENV}/python -m pip install libclang
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
endif()

message (STATUS "Generating containers for Current")
set(dgnix_DEPENDENCIES)
get_include_directories(dgnix_DEPENDENCIES dgnix)
set(DIAssets_DEPENDENCIES)
get_include_directories(DIAssets_DEPENDENCIES DIAssets)
set(ALL_DEPENDENCIES)
list(APPEND ALL_DEPENDENCIES ${dgnix_DEPENDENCIES})
list(APPEND ALL_DEPENDENCIES ${DIAssets_DEPENDENCIES})
list(REMOVE_DUPLICATES ALL_DEPENDENCIES)
string(REPLACE ";" "," add_includes "${ALL_DEPENDENCIES}")

set(in_path "${CMAKE_CURRENT_SOURCE_DIR}/${guiapp_include_dir}")
set(gen_dir "GUIApp")
execute_process(
    COMMAND ${Python3_ENV}/python generate.py ${in_path} ${out_include_path} ${out_source_path} --out_include_dir=${gen_dir} --out_source_dir=${gen_dir} --add_includes=${add_includes} --cache_path=${cache_path}
    RESULT_VARIABLE PY_OUTPUT
    WORKING_DIRECTORY ${DIAssets_SOURCE_DIR}/utils/generator
    )

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

file(RELATIVE_PATH RESOURCE_PATH ${PROJECT_BINARY_DIR} ${assets_dir})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.dat.in ${PROJECT_BINARY_DIR}/settings.dat)
