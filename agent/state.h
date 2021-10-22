/// define the agent struct
#pragma once

#include "point.h"

#include <string>
#include <vector>
#include <memory>

namespace av {

struct Waypoint {
  double time{0.};
  double s{0.};
  double l{0.};
  
  double x{0.};
  double y{0.};
  double z{0.};
};

struct Trajectory {
  double probability{0.};
  std::string generator{};

  std::vector<Waypoint> points{};
};

struct Operation {
  double throttle_pedal{0.};
  double brake_pedal{0.};
};

struct State {
  enum class Type { UNKNOWN, PEDESTRIAN, BICYCLE, VEHICLE, EGO };

  std::string id{};
  Type type{Type::UNKNOWN};
  double time{0.};

  std::vector<Point3d> shape{};
  Point3d position{};
  Point3d velocity{};
  double heading{0.};
  std::shared_ptr<Operation> operation{};

  std::vector<Trajectory> futures{};
};

}  // namespace av
