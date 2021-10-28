/// viewer option
#pragma once

#include "feature.h"
#include "map_graph.h"
#include "agent_pool.h"

namespace av {

/// Update view option
class ViewerOption final : public Feature {
 public:
  ViewerOption() = delete;
  virtual ~ViewerOption() = default;
  /// Constructor
  ViewerOption(MapGraph* m, AgentPool* ap);

  /// Implement interface
  void Execute(Config*);

 private:
  void SetDefaultCenter(Config* conf);

  MapGraph* map_{nullptr};
  AgentPool* agents_{nullptr};
};

}  // namespace av
