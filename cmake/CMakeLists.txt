cmake_minimum_required(VERSION 3.16)

project(dizidler)

include(../../tools/CMakeCommon.cmake)

verifyCppCompiler(8 6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdl2)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_compile_definitions(DEFINITELY_SINGLE_THREAD _DEBUG)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--export-dynamic,--no-as-needed")
target_link_libraries(${PROJECT_NAME} ${CMAKE_EXE_LINKER_FLAGS} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} SDL2::Main SDL2::Image SDL2::Mixer SegFault)
