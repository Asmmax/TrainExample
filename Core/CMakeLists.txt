cmake_minimum_required (VERSION 3.8)

generate_di_files(TARGET Core)

file(GLOB_RECURSE cur_include "${DI_CURRENT_INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE cur_src "${DI_CURRENT_SOURCE_DIR}/*.cpp")

file(GLOB_RECURSE gen_include "${DI_CURRENT_OUT_INCLUDE_PATH}/*.hpp")
file(GLOB_RECURSE gen_src "${DI_CURRENT_OUT_SOURCE_PATH}/*.cpp")

add_library (Core STATIC
${cur_include}
${cur_src}
${gen_include}
${gen_src})

target_compile_features (Core PRIVATE cxx_std_17)
target_include_directories(Core 
PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
PUBLIC "${DI_CURRENT_OUT_INCLUDE_PATH}")

target_link_libraries(Core PUBLIC DIAssets PUBLIC dgnix PRIVATE $<$<PLATFORM_ID:Windows>:winmm> PUBLIC $<$<AND:$<PLATFORM_ID:Linux>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
setup_di_cache(TARGET Core)
