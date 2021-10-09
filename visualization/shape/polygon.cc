#include "polygon.h"

namespace av {

Polygon::Polygon(const std::vector<ImVec2>& pts) : points_{pts} {}

Polygon::Polygon(const std::vector<ImVec2>& pts, const Style& stye)
    : Shape(stye), points_{pts} {}

std::vector<ImVec2>* Polygon::points() { return &points_; }

void Polygon::Draw() {
  auto sty = Shape::style();
  auto col = IM_COL32(sty->color.r, sty->color.g, sty->color.b, sty->color.a);
  if (sty->is_fill) {
    ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(
        points_.data(), points_.size(), col);
  } else {
    points_.push_back(points_.front());
    ImGui::GetBackgroundDrawList()->AddPolyline(
        points_.data(), points_.size(), col, 0, sty->width);
    points_.pop_back();
  }
  if (sty->text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(
      points_.front(), col, sty->text.c_str());
}

}  // namesapce av
