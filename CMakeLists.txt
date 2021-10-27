cmake_minimum_required(VERSION 3.10)
project(visualizer)

cmake_policy(SET CMP0027 NEW)
# Set build mode
set(CMAKE_CXX_COMPILER /usr/bin/g++ CACHE PATH "")
set(CXX_OPTIONS "-Wall -Wextra -pthread -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_OPTIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_OPTIONS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_BUILD_TYPE "DEBUG")


file(GLOB_RECURSE CMAKE_FILES "${CMAKE_SOURCE_DIR}/cmake/*.cmake")
foreach(CMAKE_FILE ${CMAKE_FILES})
  include(${CMAKE_FILE})
endforeach()

include_directories(
  /usr/include/SDL2
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agent
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agent/extractors
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common/geometry
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature/features
  ${CMAKE_CURRENT_SOURCE_DIR}/src/map
  ${CMAKE_CURRENT_SOURCE_DIR}/src/option
  ${CMAKE_CURRENT_SOURCE_DIR}/src/option/options
  ${CMAKE_CURRENT_SOURCE_DIR}/src/visualization
  ${CMAKE_CURRENT_SOURCE_DIR}/src/visualization/renderers
)

link_directories(
  /usr/bin
)

# Libs
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

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
message(${SRCS})

add_executable(
  ${PROJECT_NAME}
  ${IMGUI_SRCS}
  ${SRCS}
  main.cc
  )

target_link_libraries(
  ${PROJECT_NAME} 
  dl
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
  cyber
  gflags
  glog
  protobuf
  )
