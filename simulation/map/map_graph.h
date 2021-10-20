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
  MapGraph& operator=(const MapGraph&) = default;
  /// Move constructor
  MapGraph(MapGraph&&) = default;
  /// Move operator
  MapGraph& operator=(MapGraph&&) = default;

  /// Add node to graph
  void AddLaneNode(LaneNode&& node);
  /// Add edge
  void AddConnectEdge(const std::string& from, const std::string& to);

  /// Get node from graph by node id
  LaneNode* GetNode(const std::string& id);
  /// Get successor nodes from graph by node id
  std::unordered_set<std::string> GetNextNodes(const std::string& id);
  /// Get all nodes
  std::vector<std::string> GetAllNodes();

 private:
  std::unordered_map<std::string, LaneNode> nodes_{};
  std::unordered_map<std::string, std::unordered_set<std::string>> edges_{};
};

}  // namespace av
