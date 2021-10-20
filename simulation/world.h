/// Define the simulation world
#pragma once

#include "simulation/map/map_graph.h"
#include "shape.h"

namespace av {

/// Confs about gui
struct GuiView {
  double window_width{0.};
  double window_height{0.};
  double window_center_x{0.};
  double window_center_y{0.};

  double zoom_ratio{1.};

  double real_center_heading{0.};
  double real_center_x{0.};
  double real_center_y{0.};
};


/// Hold the simulation world
class World {
 public:
  World();

  /// Draw the world
  void Draw();

  /// GetGuiViewConf
  GuiView* GetGuiViewConf();

 private:
  void DrawMap();
  void DrawLane(const std::string& id);

 private:
  MapGraph map_{};
  std::unordered_map<std::string, std::array<Waypoint, 2>> lane_limit_pts_{};
  GuiView gui_view_{};
  Window draw_window_{};
};

}  // namespace av
