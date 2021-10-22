#include "apollo_map.h"

#include <fstream>
#include <iostream>

#include "map.pb.h"

namespace av {

MapGraph ApolloMap::InitMap(const std::string& path) const {
  MapGraph graph{};
  neodrive::global::hdmap::Map proto_map{};
  std::fstream input(path, std::ios::in | std::ios::binary);
  std::cout << "load map from: " << path << std::endl;
  if (!input.good() || !proto_map.ParseFromIstream(&input)) {
    std::cout << "failed!" << std::endl;
    return graph;
  }
  std::cout << "successfully!" << std::endl;

  // Build graph
  std::cout << "proto lane_size: " << proto_map.lane_size() << std::endl;
  for (const auto& lane : proto_map.lane()) {
    // Add node
    LaneNode node{.id = lane.id().id()};
    // Center line
    for (const auto& curve : lane.central_curve().segment()) {
      if (!curve.has_line_segment()) continue;
      for (auto& p : curve.line_segment().point()) {
        node.center_line.push_back({p.x(), p.y(), p.z()});
      }
    }
    // Left boundary
    for (const auto& curve : lane.left_boundary().curve().segment()) {
      if (!curve.has_line_segment()) continue;
      for (auto& p : curve.line_segment().point()) {
        node.left_bound.push_back({p.x(), p.y(), p.z()});
      }
    }
    // Right boundary
    for (const auto& curve : lane.right_boundary().curve().segment()) {
      if (!curve.has_line_segment()) continue;
      for (auto& p : curve.line_segment().point()) {
        node.right_bound.push_back({p.x(), p.y(), p.z()});
      }
    }
    graph.AddLaneNode(std::move(node));

    /// Add edge
    for (const auto& next : lane.successor_id()) {
      graph.AddConnectEdge(lane.id().id(), next.id());
    }
  }

  return graph;
}

}  // namespace av
