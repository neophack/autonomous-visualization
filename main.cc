#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <iostream>

#include "visualization/shape/circle.h"
#include "visualization/shape/polyline.h"
#include "visualization/shape/polygon.h"
#include "visualization/shape/rectangle.h"
#include "visualization/shape/triangle.h"
#include "visualization/shape/quadrilateral.h"
#include "simulation/world.h"

void ShowGraph() {
  // circle
  av::Circle{{50, 50}, 50., av::Style{.text = "This\nis\na\ncircle"}}.Draw();
  av::Circle{{150, 50}, 50., av::Style{.is_fill = true}}.Draw();
  // polyline
  av::PolyLine{{{0, 150}, {50, 150}, {100, 100}, {150, 130}},
               av::Style{.text = "a\npolyline"}}.Draw();
  av::PolyLine{{{200, 150}, {250, 150}, {300, 100}, {350, 130}},
               av::Style{.color = {255, 128, 255, 255}}}.Draw();
  // polyline
  av::Polygon{{{0, 300}, {50, 250}, {100, 250}, {150, 300}, {100, 350}},
              av::Style{.text = "a\npolygon"}}.Draw();
  av::Polygon{{{100, 300}, {150, 250}, {200, 250}, {250, 300}, {200, 350}},
              av::Style{.is_fill = true}}.Draw();
  // rectangle
  av::Rectangle{{{{0, 400}, {100, 450}}},
                av::Style{.color = {0, 0, 240, 200}}}.Draw();
  av::Rectangle{{{{100, 400}, {200, 450}}},
                av::Style{.color = {0, 255, 240, 200}, .is_fill=true}}.Draw();
  // triangle
  av::Triangle{{{{0, 500}, {100, 550}, {50, 500}}},
               av::Style{.color = {0, 0, 240, 200}}}.Draw();
  av::Triangle{{{{100, 500}, {200, 550}, {250, 500}}},
               av::Style{.color = {255, 0, 240, 200}, .is_fill=true}}.Draw();
  // quadrilateral
  av::Quadrilateral{{{{0, 600}, {100, 650}, {80, 700}, {0, 630}}},
                    av::Style{.color = {255, 0, 128, 128}}}.Draw();
  av::Quadrilateral{{{{100, 600}, {200, 650}, {180, 700}, {100, 630}}},
                    av::Style{.color = {0, 0, 128, 128}, .is_fill=true}}.Draw();

  // mainview
  auto main_view = ImGui::GetMainViewport();
  // std::cout << main_view->Size.x << ", " << main_view->Size.y << std::endl;
}

av::World world{};

// Main code
int main(int, char**) {
  // Setup SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER)) {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

  // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
  // GL 3.2 Core + GLSL 150
  const char* glsl_version = "#version 150";
  // Always required on Mac
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
      SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
      SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags =
    (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window* window =SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 1280, 720,
                                       window_flags);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Our state
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Main loop
  bool done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) done = true;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window)) done = true;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // test
    ShowGraph();

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
