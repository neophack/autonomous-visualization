#include "viewer_option.h"

#include "imgui.h"

#include <iostream>

namespace av {

ViewerOption::ViewerOption(MapGraph* m, AgentPool* ap) : map_{m}, agents_{ap} {}

void ViewerOption::Execute(Config* conf) {
  // Update window size
  auto view = ImGui::GetMainViewport();
  conf->main_view.width = view->Size.x;
  conf->main_view.height = view->Size.y;

  // update center
  SetDefaultCenter(conf);

  if (ImGui::CollapsingHeader("Viewer Option")) {
    ImGui::Text("You can now use mouse to change the view");
    double wheel = ImGui::GetIO().MouseWheel;
    if (wheel < -0.5) conf->main_view.zoom_ratio *= 1.2;
    if (wheel > 0.5) conf->main_view.zoom_ratio /= 1.2;
  }
}

void ViewerOption::SetDefaultCenter(Config* conf) {
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
