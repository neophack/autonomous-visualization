#include "apollo_map.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message.h>
#include <fstream>
#include <memory>

#include "map.pb.h"

namespace av {

MapGraph ApolloMap::InitMap(const std::string path) const {
  MapGraph graph{};

  // Load proto
  int fd = open(path.c_str(), 0_RDONLY);
  if (fd == -1) return graph;
  std::unique_ptr<ZeroCopyInputStream> raw_input =
      std::make_unique<FileInputStream>(fd);

  std::unique_ptr<CodedInputStream> coded_input =
      std::make_unique<CodedInputStream>(raw_input.get());

  coded_input->SetTotalBytesLimit(INT_MAX, 536870912);  //  0..512M..2G
  ::google::protobuf::Message proto_map{};
  bool ret = proto_map.ParseFromCodedStream(coded_input.get());
  close(fd);
  if (!ret) return graph;

  // Build graph
  for (const auto& lane : proto_map.lane()) {
    // Add node
    LaneNode node{.id = lane.id().id()};
    // Center line
    for (const auto& p : lane.central_curve().segment()) {
      node.center_line.emplace_back(
          p.start_position().x(), p.start_position().y(),
          p.start_position().z());
    }
    // Left boundary
    for (const auto& p : lane.left_boundary().curve().segment()) {
      node.left_boundary.emplace_back(
          p.start_position().x(), p.start_position().y(),
          p.start_position().z());
    }
    // Right boundary
    for (const auto& p : lane.right_boundary().curve().segment()) {
      node.right_boundary.emplace_back(
          p.start_position().x(), p.start_position().y(),
          p.start_position().z());
    }
    graph.AddLaneNode(std::move(node));

    /// Add edge
    for (const auto& next : lane.predecessor_id()) {
      graph.AddConnectEdge(lane.id().id(), next.id());
    }
  }

  return graph;
}

}  // namespace av
