/// Define the simulation world
#pragma once

#include <memory>
#include <vector>

#include "config.h"
#include "map_graph.h"
#include "agent_pool.h"
#include "value_pool.h"
#include "agent_extractor.h"
#include "value_extractor.h"
#include "feature.h"

namespace av {

/// Hold the simulation world
class World {
 public:
  /// Default constructor
  World();
  /// Destructor
  ~World() = default;
  /// Update the world contents
  void TimeGoesBy();

 private:
  Config conf_{};
  /// map
  MapGraph map_{};
  /// agent
  AgentPool agents_{};
  std::vector<std::unique_ptr<AgentExtractor>> agent_extrs_{};
  /// value
  ValuePool values_{};
  std::vector<std::unique_ptr<ValueExtractor>> value_extrs_{};
  /// features 
  std::vector<std::unique_ptr<Feature>> features_{};
};

}  // namespace av
