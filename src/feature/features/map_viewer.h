/// Visualize map graph
#pragma once

#include <memory>
#include <unordered_map>

#include "feature.h"
#include "map_graph.h"
#include "box.h"
#include "renderer.h"

namespace av {

class MapViewer final : public Feature {
 public:
  MapViewer() = delete;
  virtual ~MapViewer() = default;
  /// Can only init with map graph
  explicit MapViewer(MapGraph* m);
  /// Draw all lanes
  void Execute(Config* conf) override;

 private:
  void DrawLane(const std::string& id, const Config* conf);

  MapGraph* map_{nullptr};
  std::unique_ptr<Renderer> render_{};
  std::unordered_map<std::string, Box> lane_boxes_{};
};

}  // namespace av
