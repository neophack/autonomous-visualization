/// Update the main view config 
#pragma once

#include "option.h"
#include "map_graph.h"
#include "agent_pool.h"

namespace av {

class MainViewOption : public Option {
 public:
  MainViewOption() = delete;
  virtual ~MainViewOption() = default;

  MainViewOption(MapGraph* m, AgentPool* ap);

  void Update(Config*);

 private:
  void SetDefaultCenter(Config*);

  MapGraph* map_{nullptr};
  AgentPool* agents_{nullptr};
};

}  // namespace av
