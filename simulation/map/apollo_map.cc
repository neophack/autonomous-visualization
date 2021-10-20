#include "apollo_map.h"

#include <fstream>
#include <iostream>

#include "map.pb.h"

namespace av {

MapGraph ApolloMap::InitMap(const std::string& path) const {
  MapGraph graph{};
  neodrive::global::hdmap::Map proto_map{};
  std::fstream input(path, std::ios::in | std::ios::binary);
  std::cout << "load... map from: " << path << std::endl;
  if (!input.good() || !proto_map.ParseFromIstream(&input)) return graph;
  std::cout << "successfully!" << std::endl;

  // Build graph
  // std::cout << proto_map.DebugString() << std::endl;
  for (const auto& lane : proto_map.lane()) {
    // Add node
    LaneNode node{.id = lane.id().id()};
    // Center line
    for (const auto& p : lane.central_curve().segment()) {
      node.center_line.push_back(
          {p.start_position().x(), p.start_position().y(),
           p.start_position().z()});
    }
    // Left boundary
    for (const auto& p : lane.left_boundary().curve().segment()) {
      node.left_bound.push_back(
          {p.start_position().x(), p.start_position().y(),
           p.start_position().z()});
    }
    // Right boundary
    for (const auto& p : lane.right_boundary().curve().segment()) {
      node.right_bound.push_back(
          {p.start_position().x(), p.start_position().y(),
           p.start_position().z()});
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
