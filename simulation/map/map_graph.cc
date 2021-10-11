#include "map_graph.h"

namespace av {

MapGraph::AddLaneNode(LaneNode&& node) {
  nodes_.emplace(node.id, std::move(node));
}

MapGraph::AddConnectEdge(const std:;string& from, const std::string& to) {
  edges_[from].push_back(to);
}


}  // namespace av
