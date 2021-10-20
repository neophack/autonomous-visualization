#include "polyline.h"

namespace av {

PolyLine::PolyLine(const std::vector<ImVec2>& pts) : points_{pts} {}

PolyLine::PolyLine(const std::vector<ImVec2>& pts, const Style& style)
    : Shape(style), points_{pts} {}

std::vector<ImVec2>* PolyLine::points() { return &points_; }

void PolyLine::Draw() {
  auto sty = Shape::style();
  auto col = IM_COL32(sty->color.r, sty->color.g, sty->color.b, sty->color.a);
  ImGui::GetBackgroundDrawList()->AddPolyline(
      points_.data(), points_.size(), col, 0, sty->width);
  if (sty->text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(
      points_.front(), col, sty->text.c_str());
}

}  // namesapce av
