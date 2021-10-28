include_directories(
  /usr/include/SDL2
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends
  )
link_directories(/usr/bin)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Opengl
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Srcs
set(IMGUI_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_sdl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp
)

