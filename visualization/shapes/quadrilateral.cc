#include "quadrilateral.h"

namespace av {

Quadrilateral::Quadrilateral(const std::array<ImVec2, 4>& pts) : points_{pts} {}

Quadrilateral::Quadrilateral(const std::array<ImVec2, 4>& pts, const Style& stye)
    : Shape(stye), points_{pts} {}

std::array<ImVec2, 4>* Quadrilateral::points() { return &points_; }

void Quadrilateral::Draw() {
  auto sty = Shape::style();
  auto col = IM_COL32(sty->color.r, sty->color.g, sty->color.b, sty->color.a);
  auto& [p0, p1, p2, p3] = points_;
  if (sty->is_fill) {
    ImGui::GetBackgroundDrawList()->AddQuadFilled(p0, p1, p2, p3, col);
  } else {
    ImGui::GetBackgroundDrawList()->AddQuad(p0, p1, p2, p3, col, sty->width);
  }
  if (sty->text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(p0, col, sty->text.c_str());
}

}  // namesapce av
