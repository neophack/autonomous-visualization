#include "map_viewer.h"

#include <cmath>
#include <algorithm>
#include <iostream>

#include "imgui_2d.h"
#include "imgui.h"
#include "map/apollo_map.h"
#include "shape.h"
#include "feature_helper.h"

namespace av {

MapViewer::MapViewer(MapGraph* m) : map_{m} {
  render_ = std::make_unique<Imgui2d>();

  // Update lane box
  for (const auto& lane : map_->GetAllNodes()) {
    auto& center = map_->GetNode(lane)->center_line;
    auto& left = map_->GetNode(lane)->left_bound;
    auto& right = map_->GetNode(lane)->right_bound;
    std::vector<double> xs{};
    std::vector<double> ys{};
    for (auto& p : center) { xs.push_back(p.x); ys.push_back(p.y); }
    for (auto& p : left) { xs.push_back(p.x); ys.push_back(p.y); }
    for (auto& p : right) { xs.push_back(p.x); ys.push_back(p.y); }
    lane_boxes_[lane].lb.x = *min_element(xs.begin(), xs.end());
    lane_boxes_[lane].lb.y = *min_element(ys.begin(), ys.end());
    lane_boxes_[lane].rt.x = *max_element(xs.begin(), xs.end());
    lane_boxes_[lane].rt.y = *max_element(ys.begin(), ys.end());
  }
}

void MapViewer::Execute(Config* conf) {
  if (ImGui::CollapsingHeader("Map Viewer")) {
    ImGui::Checkbox("Is Show", &conf->map_viewer.is_show);
  }
  if (!conf->map_viewer.is_show) return;

  auto view_box = feature::GetViewBox(conf->main_view);
  for (auto& [lane_id, lane_box] : lane_boxes_) {
    if (IsOverlap(lane_box, view_box)) DrawLane(lane_id, conf);
  }
}

void MapViewer::DrawLane(const std::string& id, const Config* conf) {
  if (!map_) return;
  auto node = map_->GetNode(id);

  // Extract boundary
  Style bound_style{.color = conf->map_viewer.bound_col,
                    .width = conf->map_viewer.bound_width};
  Polyline left{.style = bound_style};
  for (auto& p : node->left_bound) left.points.push_back(
      feature::ToGuiView(feature::To2d(p), conf->main_view));
  Polyline right{.style = bound_style};
  for (auto& p : node->right_bound) right.points.push_back(
      feature::ToGuiView(feature::To2d(p), conf->main_view));

  // Extract center
  Style center_style{.color = conf->map_viewer.center_col,
                     .width = conf->map_viewer.center_width};
  if (conf->map_viewer.is_show_lane_id) center_style.text = id;
  Polyline center{.style = center_style};
  for (auto& p : node->center_line) center.points.push_back(
      feature::ToGuiView(feature::To2d(p), conf->main_view));

  // Draw
  render_->Draw(left);
  render_->Draw(right);
  render_->Draw(center);
}

}  // namespace av
