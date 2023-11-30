cmake_minimum_required (VERSION 3.8)

generate_di_files(TARGET Input DEPS Core)

file(GLOB_RECURSE cur_include "${DI_CURRENT_INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE cur_src "${DI_CURRENT_SOURCE_DIR}/*.cpp")

file(GLOB_RECURSE gen_include "${DI_CURRENT_OUT_INCLUDE_PATH}/*.hpp")
file(GLOB_RECURSE gen_src "${DI_CURRENT_OUT_SOURCE_PATH}/*.cpp")

add_library (Input STATIC
${cur_include}
${cur_src}
${gen_include}
${gen_src})

target_compile_features (Input PRIVATE cxx_std_17)
target_include_directories(Input 
PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
PUBLIC "${DI_CURRENT_OUT_INCLUDE_PATH}")

target_link_libraries(Input PRIVATE Core)
setup_di_cache(TARGET Input)
