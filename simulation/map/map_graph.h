/// Define the graph of map
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace av {

/// Waypoint struct
struct WayPoint {
  double x{0.};
  double y{0.};
  double z{0.};
};

/// Overlap to describe markers(crosswalk, array, etc.)
struct Overlap {
  double s{0.};
  double length{0.};

  std::string type{};
};

/// Define the graph node to represent lane
struct LaneNode {
  std::string id{};

  std::vector<WayPoint> center_line{};
  std::vector<WayPoint> left_bound{};
  std::vector<WayPoint> right_bound{};
};

/// Define the graph for map
class MapGraph {
 public:
  /// Default constructor
  MapGraph() = default;
  /// Copy constructor
  MapGraph(const MapGraph&) = default;
  /// Copy operator
  MapGraph& operator=MapGraph(const MapGraph&) = default;
  /// Move constructor
  MapGraph(MapGraph&&) = default;
  /// Move operator
  MapGraph& operator=MapGraph(MapGraph&&) = default;

  /// Add node to graph
  void AddLaneNode(LaneNode&& node);
  /// Add edge
  void AddConnectEdge(const std::string& from, const std::string& to);

  /// Draw the map
  void Draw();

 private:
  std::unordered_map<std::string, LaneNode> nodes_{};
  std::unordered_map<std::string, std::unordered_set<std::string>> edges_{};
};

}  // namespace av
