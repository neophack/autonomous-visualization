#include "world.h"

#include "apollo_map.h"
#include "apollo_channel.h"
#include "main_view_option.h"
#include "map_viewer.h"
#include "agent_viewer.h"

namespace av {

World::World() {
  // map
  map_ = ApolloMap{}.InitMap(conf_.world.map_path);

  // agent
  agent_extractors_.push_back(std::move(std::make_unique<ApolloChannel>()));

  // option
  options_.push_back(std::move(
      std::make_unique<MainViewOption>(&map_, &agents_)));

  // functions
  funcs_.push_back(std::move(std::make_unique<MapViewer>(&map_)));
  funcs_.push_back(std::move(std::make_unique<AgentViewer>(&agents_)));
}

void World::TimeGoesBy() {
  // Update data
  // agent
  for (auto& e : agent_extractors_) {
    for (auto& s : e->ExtractStates()) { agents_.Update(std::move(s)); }
  }

  // Update option
  for (auto& o : options_) o->Update(&conf_);

  // Execute funcs
  for (auto& f : funcs_) f->Execute(&conf_);
}

}  // namespace av
