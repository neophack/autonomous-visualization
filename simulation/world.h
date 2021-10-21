/// Define the simulation world
#pragma once

#include <memory>

#include "map_graph.h"
#include "box.h"
#include "renderer.h"

namespace av {

/// Confs about gui
struct ViewWindow {
  double window_width{0.};
  double window_height{0.};

  double zoom_ratio{1.};

  double world_center_heading{0.};
  double world_center_x{0.};
  double world_center_y{0.};
};


/// Hold the simulation world
class World {
 public:
  World();

  /// Draw the world
  void Draw();

  /// Draw the demo shape
  void DrawDemo();

  /// GetGuiViewConf
  ViewWindow* GetGuiViewConf();

 private:
  void DrawMapInBox(const Box& box);
  void DrawLaneView(const std::string& id, const ViewWindow& view);

 private:
  MapGraph map_{};
  std::unique_ptr<Renderer> render_{};
  std::unordered_map<std::string, Box> lane_boxes_{};
  ViewWindow gui_view_{};
};

}  // namespace av
