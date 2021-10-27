#include "main_view_option.h"

#include "imgui.h"

#include <iostream>

namespace av {

MainViewOption::MainViewOption(MapGraph* m, AgentPool* ap)
    : map_{m}, agents_{ap} {}

void MainViewOption::Update(Config* conf) {
  // update window
  auto view = ImGui::GetMainViewport();
  conf->main_view.width = view->Size.x;
  conf->main_view.height = view->Size.y;

  // Update ratio
  double wheel = ImGui::GetIO().MouseWheel;
  if (wheel < -0.5) conf->main_view.zoom_ratio *= 1.2;
  if (wheel > 0.5) conf->main_view.zoom_ratio /= 1.2;

  // update center
  SetDefaultCenter(conf);
}

void MainViewOption::SetDefaultCenter(Config* conf) {
  if (auto ego = agents_->GetAgent("Ego"); ego) {  // Has ego car
    conf->main_view.center.x = ego->GetLatestState()->position.x;
    conf->main_view.center.y = ego->GetLatestState()->position.y;
    conf->main_view.center.heading = ego->GetLatestState()->heading;
  } else {  // Map random lane
    auto nodes = map_->GetAllNodes();
    auto node = map_->GetNode(nodes.front());
    conf->main_view.center.x = node->center_line.front().x;
    conf->main_view.center.y = node->center_line.front().y;
  }
}

}  // namespace av
