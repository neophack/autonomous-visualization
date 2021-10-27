/// Define the simulation world
#pragma once

#include <memory>
#include <vector>

#include "config.h"
#include "map_graph.h"
#include "agent_pool.h"
#include "state_extractor.h"
#include "feature.h"
#include "option.h"

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
  std::vector<std::unique_ptr<StateExtractor>> agent_extractors_{};
  /// options
  std::vector<std::unique_ptr<Option>> options_{};
  /// functions
  std::vector<std::unique_ptr<Feature>> funcs_{};
};

}  // namespace av
