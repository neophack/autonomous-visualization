#include "world.h"

#include <cmath>
#include <algorithm>
#include <iostream>

#include "imgui_2d.h"
#include "map/apollo_map.h"
#include "shape.h"

// unnamed namespace
namespace {

av::Box GetViewBox(const av::ViewWindow& view) {
  double sin_h = std::sin(view.world_center_heading);
  double cos_h = std::cos(view.world_center_heading);
  av::Point2d cen{view.world_center_x, view.world_center_y};
  double half_w = view.window_width / 2;
  double half_h = view.window_height / 2;

  std::vector<double> xs{half_w * cos_h + half_h * sin_h,
                         half_w * cos_h - half_h * sin_h,
                         -half_w * cos_h + half_h * sin_h,
                         -half_w * cos_h - half_h * sin_h};
  std::vector<double> ys{half_w * sin_h + half_h * cos_h,
                         half_w * sin_h - half_h * cos_h,
                         -half_w * sin_h + half_h * cos_h,
                         -half_w * sin_h - half_h * cos_h};
  std::sort(xs.begin(), xs.end());
  std::sort(ys.begin(), ys.end());
  return {av::Point2d{xs.front(), ys.front()} * view.zoom_ratio + cen,
          av::Point2d{xs.back(), ys.back()} * view.zoom_ratio + cen};
}

av::Point2d To2d(const av::Point3d& p) { return {p.x, p.y}; }

av::Point2d ToGuiView(const av::Point2d& p, const av::ViewWindow& view) {
  auto res = p - av::Point2d{view.world_center_x, view.world_center_y};
  res = Rotate(res, view.world_center_heading);
  res /= view.zoom_ratio;
  res.y += view.window_height / 2;
  res.x += view.window_width / 2;
  return res;
}

}  // namespace

namespace av {

World::World() {
  // map_ = ApolloMap{}.InitMap("/home/caros/adu_data/map/map/base_map.bin");
  map_ = ApolloMap{}.InitMap("/home/caros/adu_data/map/shougang_map/base_map.bin");

  double min_x = std::numeric_limits<double>::max();
  double min_y = std::numeric_limits<double>::max();
  double max_x = std::numeric_limits<double>::lowest();
  double max_y = std::numeric_limits<double>::lowest();

  // Update lane box
  for (const auto& lane : map_.GetAllNodes()) {
    auto& center = map_.GetNode(lane)->center_line;
    auto& left = map_.GetNode(lane)->left_bound;
    auto& right = map_.GetNode(lane)->right_bound;
    std::vector<double> xs{};
    std::vector<double> ys{};
    for (auto& p : center) { xs.push_back(p.x); ys.push_back(p.y); }
    for (auto& p : left) { xs.push_back(p.x); ys.push_back(p.y); }
    for (auto& p : right) { xs.push_back(p.x); ys.push_back(p.y); }
    lane_boxes_[lane].lb.x = *min_element(xs.begin(), xs.end());
    lane_boxes_[lane].lb.y = *min_element(ys.begin(), ys.end());
    lane_boxes_[lane].rt.x = *max_element(xs.begin(), xs.end());
    lane_boxes_[lane].rt.y = *max_element(ys.begin(), ys.end());

    min_x = std::min(min_x, lane_boxes_[lane].lb.x);
    min_y = std::min(min_y, lane_boxes_[lane].lb.y);
    max_x = std::max(max_x, lane_boxes_[lane].rt.x);
    max_y = std::max(max_y, lane_boxes_[lane].rt.y);
  }

  render_ = std::make_unique<Imgui2d>();
  gui_view_.world_center_x = (min_x + max_x) / 2;
  gui_view_.world_center_y = (min_y + max_y) / 2;
}

void World::Draw() {
  auto view_box = GetViewBox(gui_view_);
  std::cout << "view box: (" << view_box.lb.x << ", " << view_box.lb.y << "), (" 
            << view_box.rt.x << ", " << view_box.rt.y << ")" << std::endl;
  DrawMapInBox(view_box);
}

void World::DrawDemo() {
  // circle
  // std::cout << "Start draw demo..." << std::endl;
  render_->Draw(av::Circle{{.text = "A\ncircle"}, {50, 50}, 50.});
  render_->Draw(av::Circle{{.is_fill = true}, {150, 50}, 50.});
  // polyline
  render_->Draw(av::Polyline{{.text = "a\npolyline"},
      {{0, 150}, {50, 150}, {100, 100}, {150, 130}}});
  render_->Draw(av::Polyline{{.color = {255, 128, 255, 255}},
      {{200, 150}, {250, 150}, {300, 100}, {350, 130}}});
  // polyline
  render_->Draw(av::Polygon{{.text = "a\npolygon"},
      {{0, 300}, {50, 250}, {100, 250}, {150, 300}, {100, 350}}});
  render_->Draw(av::Polygon{{.is_fill = true},
      {{100, 300}, {150, 250}, {200, 250}, {250, 300}, {200, 350}}});
  // rectangle
  render_->Draw(av::Rectangle{{.color = {0, 0, 240, 200}},
      {{{0, 400}, {100, 450}}}});
  render_->Draw(av::Rectangle{{.color = {0, 255, 240, 200}, .is_fill=true},
      {{{100, 400}, {200, 450}}}});
  // triangle
  render_->Draw(av::Triangle{{.color = {0, 0, 240, 200}},
      {{{0, 500}, {100, 550}, {50, 500}}}});
  render_->Draw(av::Triangle{{.color = {255, 0, 240, 200}, .is_fill=true},
      {{{100, 500}, {200, 550}, {250, 500}}}});
  // quadrilateral
  render_->Draw(av::Quadrilateral{{.color = {255, 0, 128, 128}},
      {{{0, 600}, {100, 650}, {80, 700}, {0, 630}}}});
  render_->Draw(av::Quadrilateral{{.color = {0, 0, 128, 128}, .is_fill=true},
      {{{100, 600}, {200, 650}, {180, 700}, {100, 630}}}, });

  // mainview
  // auto main_view = ImGui::GetMainViewport();
  // std::cout << main_view->Size.x << ", " << main_view->Size.y << std::endl;
}

void World::DrawMapInBox(const Box& view_box) {
  for (const auto& [lane_id, lane_box]: lane_boxes_) {
    if (!IsOverlap(lane_box, view_box)) continue;
    DrawLaneView(lane_id, gui_view_);
  }
}

void World::DrawLaneView(const std::string& id, const ViewWindow& view) {
  Style style{.color={0, 0, 0, 255}, .width=1};
  auto node = map_.GetNode(id);

  /// Extract points
  Polyline left{.style=style};
  for (auto& p : node->left_bound) left.points.push_back(
      ToGuiView(To2d(p), view));
  Polyline right{.style=style};
  for (auto& p : node->right_bound) right.points.push_back(
      ToGuiView(To2d(p), view));
  style.color = {255, 0, 0, 255};
  // style.text = id;
  Polyline center{.style=style};
  for (auto& p : node->center_line) center.points.push_back(
      ToGuiView(To2d(p), view));
  //std::cout << "p0: (" << left.points.back().x << ", "
  //          << left.points.back().y << ")" << std::endl;
  //std::cout << "p1: (" << right.points.back().x << ", "
  //          << right.points.back().y << ")" << std::endl;

  // Draw
  render_->Draw(left);
  render_->Draw(right);
  render_->Draw(center);
}

ViewWindow* World::GetGuiViewConf() { return &gui_view_; }

}  // namespace av
