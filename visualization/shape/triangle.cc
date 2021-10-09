#include "triangle.h"

namespace av {

Triangle::Triangle(const std::array<ImVec2, 3>& pts) : points_{pts} {}

Triangle::Triangle(const std::array<ImVec2, 3>& pts, const Style& stye)
    : Shape(stye), points_{pts} {}

std::array<ImVec2, 3>* Triangle::points() { return &points_; }

void Triangle::Draw() {
  auto sty = Shape::style();
  auto col = IM_COL32(sty->color.r, sty->color.g, sty->color.b, sty->color.a);
  auto& [p0, p1, p2] = points_;
  if (sty->is_fill) {
    ImGui::GetBackgroundDrawList()->AddTriangleFilled(p0, p1, p2, col);
  } else {
    ImGui::GetBackgroundDrawList()->AddTriangle(p0, p1, p2, col, sty->width);
  }
  if (sty->text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(p0, col, sty->text.c_str());
}

}  // namesapce av
