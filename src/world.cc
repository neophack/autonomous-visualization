#include "world.h"

#include "apollo_map.h"
#include "apollo_channel_agent.h"
#include "apollo_channel_value.h"

#include "viewer_option.h"
#include "map_viewer.h"
#include "agent_viewer.h"
#include "value_ploter.h"

namespace av {

World::World() {
  // Map
  map_ = ApolloMap{}.InitMap(conf_.map_viewer.map_path);

  // Agent
  agent_extrs_.push_back(std::move(std::make_unique<ApolloChannelAgent>()));

  // Value 
  value_extrs_.push_back(std::move(std::make_unique<ApolloChannelValue>()));

  // Feature
  features_.push_back(std::move(
        std::make_unique<ViewerOption>(&map_, &agents_)));
  features_.push_back(std::move(std::make_unique<MapViewer>(&map_)));
  features_.push_back(std::move(std::make_unique<AgentViewer>(&agents_)));
  features_.push_back(std::move(std::make_unique<ValuePloter>(&values_)));
}

void World::TimeGoesBy() {
  // Update agent
  for (auto& e : agent_extrs_) {
    for (auto& s : e->ExtractStates()) { agents_.Update(std::move(s)); }
  }

  // Update values
  for (auto& e : value_extrs_) {
    for (auto& [id, v] : e->ExtractValues()) { values_.UpdateValue(id, v); }
  }

  // Execute features
  for (auto& f : features_) f->Run(&conf_);
}

}  // namespace av
