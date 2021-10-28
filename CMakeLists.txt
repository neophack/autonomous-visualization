cmake_minimum_required(VERSION 3.10)
project(visualizer)

cmake_policy(SET CMP0027 NEW)

# Set build mode
set(CMAKE_CXX_COMPILER /usr/bin/g++ CACHE PATH "")
set(CXX_OPTIONS "-Wall -Wextra -pthread -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_OPTIONS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Set debug mode
set(CMAKE_BUILD_TYPE "DEBUG")

# Add all libs
file(GLOB_RECURSE CMAKE_FILES "${CMAKE_SOURCE_DIR}/cmake/*.cmake")
foreach(CMAKE_FILE ${CMAKE_FILES})
  include(${CMAKE_FILE})
endforeach()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agent
  ${CMAKE_CURRENT_SOURCE_DIR}/src/agent/extractors
  ${CMAKE_CURRENT_SOURCE_DIR}/src/value
  ${CMAKE_CURRENT_SOURCE_DIR}/src/value/extractors
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common/geometry
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature
  ${CMAKE_CURRENT_SOURCE_DIR}/src/feature/features
  ${CMAKE_CURRENT_SOURCE_DIR}/src/map
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shape
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shape/renderers
)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")

add_executable(
  ${PROJECT_NAME}
  ${IMGUI_SRCS}
  ${IMPLOT_SRCS}
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
