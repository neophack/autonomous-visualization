#include "agent_viewer.h"
#include "shape.h"
#include "imgui_2d.h"
#include "feature_helper.h"

#include <iostream>

namespace av {

AgentViewer::AgentViewer(AgentPool* ap) : agents_{ap} {
  render_ = std::make_unique<Imgui2d>();
}

void AgentViewer::Execute(Config* conf) {
  if (!agents_) return;

  // Obstacle
  Style his_style{.color = conf->agent_viewer.history_col,
                  .width = conf->agent_viewer.history_width};
  Style fut_style{.color = conf->agent_viewer.future_col,
                  .width = conf->agent_viewer.future_width};
  Style shp_style{.color = conf->agent_viewer.shape_col,
                  .is_fill = conf->agent_viewer.is_shape_filled,
                  .width = conf->agent_viewer.shape_width};

  auto view_box = feature::GetViewBox(conf->main_view);

  for (auto& id : agents_->GetAllAgentIds()) {
    auto agent = agents_->GetAgent(id);

    // history
    bool is_show{false};
    Polyline his{.style = his_style};
    for (const auto& s : *agent->GetHistory()) {
      auto p = feature::To2d(s.position);
      is_show = is_show || IsPointInBox(p, view_box);
      his.points.push_back(feature::ToGuiView(p, conf->main_view));
    }
    if (is_show) render_->Draw(his);

    // shape
    is_show = false;
    Polygon shp{.style = shp_style};
    if (id == "Ego") shp.style.color = {125, 255, 125, 125};
    if (conf->agent_viewer.is_show_id) shp.style.text = id;
    for (const auto& p : agent->GetLatestState()->shape) {
      auto p2 = feature::To2d(p);
      is_show = is_show || IsPointInBox(p2, view_box);
      shp.points.push_back(feature::ToGuiView(p2, conf->main_view));
    }
    if (is_show) render_->Draw(shp);

    // futures
    is_show = false;
    for (const auto& traj : agent->GetLatestState()->futures) {
      Polyline fut{.style = fut_style};
      if (id == "Ego") fut.style.color = {255, 255, 0, 255};
      auto& [prob, gen, pts] = traj;
      for (auto& p : pts) {
        Point2d p2{p.x, p.y};
        is_show = is_show || IsPointInBox(p2, view_box);
        fut.points.push_back(feature::ToGuiView(p2, conf->main_view));
      }
      if (is_show) render_->Draw(fut);
      is_show = false;
    }
  }
}

}  // namespace av
