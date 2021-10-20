#include "world.h"
#include "map/apollo_map.h"

namespace av {

// unnamed namespace
namespace {

std::array<std::array<double, 2>, 4> GetViewWindow(const GuiView& view) {
  double sin_h = std::sin(-view_.real_center_heading);
  double cos_h = std::cos(-view_.real_center_heading);
  double cx = gui_view_.real_center_x;
  double cy = gui_view_.real_center_y;
  double half_w = view_.width / 2;
  double half_h = view_.width / 2;
  return {{-half_w * cos_h - half_h * sin_h + cx,
           -half_w * sin_H + half_h * cos_h + cy},
         {-half_w * cos_h - -half_h * sin_h + cx,
          -half_w * sin_H + -half_h * cos_h + cy},
         {half_w * cos_h - -half_h * sin_h + cx,
          half_w * sin_H + -half_h * cos_h + cy},
         {half_w * cos_h - half_h * sin_h + cx,
          half_w * sin_H + half_h * cos_h + cy}};
}

}

World::World() {
  map_ = ApolloMap{}.InitMap("/home/caros/adu_data/map/map/base_map.bin");

  // Update left bottom and right top point to determin if draw the lane
  for (const auto& lane : map_.GetAllNodes) {
    lane_limit_pts_[lane.id][0] = min(
        {*min_element(lane.center_line.begin(), lane.center_line.end()),
         *min_element(lane.left_bound.begin(), lane.left_bound.end()),
         *min_element(lane.right_bound.begin(), lane.right_bound.end())});
    lane_limit_pts_[lane.id][1] = max(
        {*max_element(lane.center_line.begin(), lane.center_line.end()),
         *max_element(lane.left_bound.begin(), lane.left_bound.end()),
         *max_element(lane.right_bound.begin(), lane.right_bound.end())});
  }
}

void World::Draw() {
  DrawMap();
}

void World::DrawMap() {
  for (const auto& lane : map_.GetAllNodes()) {
    gui_view_.real_center_x = (lane_limit_pts_[lane.id][0].x +
                               lane_limit_pts_[lane.id][1].x) / 2.;
    gui_view_.real_center_y = (lane_limit_pts_[lane.id][0].y +
                               lane_limit_pts_[lane.id][1].y) / 2.;
    DrawLane(lane);
    break;
  }
}

GuiView* World::GetGuiViewConf() { return &gui_view_; }

void World::DrawLane(const std::string& id) {
  double min_x = gui_view_.real_center_x - 
}

}  // namespace av
