#include "map_graph.h"

#include <iostream>

namespace av {

void MapGraph::AddLaneNode(LaneNode&& node) {
  nodes_.emplace(node.id, std::move(node));
}

void MapGraph::AddConnectEdge(const std::string& from, const std::string& to) {
  edges_[from].insert(to);
}

LaneNode* MapGraph::GetNode(const std::string& id) {
  return nodes_.count(id) ? &nodes_[id] : nullptr;
}

std::unordered_set<std::string> MapGraph::GetNextNodes(const std::string& id) {
  return nodes_.count(id) ? edges_[id] : std::unordered_set<std::string>{};
}

std::vector<std::string> MapGraph::GetAllNodes() {
  std::vector<std::string> res{};
  for (auto& [id, node] : nodes_) res.push_back(id);
  return res;
}


}  // namespace av
