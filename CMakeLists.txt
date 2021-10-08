cmake_minimum_required(VERSION 3.10)
project(visualizer)

cmake_policy(SET CMP0027 NEW)
# Set build mode
set(CMAKE_CXX_COMPILER /usr/bin/g++ CACHE PATH "")
set(CXX_OPTIONS "-Wall -Wformat")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_OPTIONS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(
  /usr/include/SDL2
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends
)

link_directories(
  /usr/bin
)

# Libs
## SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(IMGUI_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_sdl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp
)

message(${SDL2_LIBRARIES})
message(${OPENGL_LIBRARIES})
add_executable(${PROJECT_NAME} ${IMGUI_SRCS} main.cc)
target_link_libraries(${PROJECT_NAME} dl ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
