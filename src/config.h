/// Define all the configs about the world
#pragma once

#include "point.h"
#include "shape.h"

namespace av {

/// Confs about gui
struct MainViewConf {
  double width{0.};
  double height{0.};

  double zoom_ratio{0.05};

  HeadingPoint center{458446, 4403850, 0};
};

struct MapViewerConf {
  bool is_show{true};

  std::string map_path{"/home/caros/data/map/map_yizhuang/base_map.bin"};

  Color bound_col{255, 255, 255, 60};  // black
  Color center_col{0, 0, 0, 125};  // red
  double bound_width{3.};
  double center_width{3.};
  bool is_show_lane_id{false};
};

struct AgentViewerConf {
  bool is_show{true};

  Color history_col{0, 255, 0, 255};
  double history_width{1.};

  Color future_col{0, 0, 255, 255};
  double future_width{1.};

  Color shape_col{0, 255, 255, 255};
  double shape_width{1.};
  bool is_shape_filled{true};
  bool is_show_id{false};
};

struct ValueViewerConf {
  bool is_show{true};
};

struct Config {
  /// Features
  MainViewConf main_view{};
  MapViewerConf map_viewer{};
  AgentViewerConf agent_viewer{};
  ValueViewerConf value_viewer{};
};

}  // namespace av
