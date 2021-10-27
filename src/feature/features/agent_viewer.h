/// Visualize map graph
#pragma once

#include "feature.h"
#include "agent_pool.h"
#include "renderer.h"

namespace av {

class AgentViewer : public Feature {
 public:
  AgentViewer() = delete;
  virtual ~AgentViewer() = default;

  explicit AgentViewer(AgentPool* ap);

  void Execute(Config* conf) override;

 private:
  AgentPool* agents_{nullptr};
  std::unique_ptr<Renderer> render_{};
};

}  // namespace av
