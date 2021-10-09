#include "circle.h"

#include "imgui.h"

namespace av {

Circle::Circle(const ImVec2& c, const double r) : center_{c}, radius_{r} {}

Circle::Circle(const ImVec2& c, const double r, const Style& style)
    : Shape(style), center_{c}, radius_{r} {};

void Circle::Draw() {
  auto sty = Shape::style();
  auto col = IM_COL32(sty->color.r, sty->color.g, sty->color.b, sty->color.a);
  if (sty->is_fill) {
    ImGui::GetBackgroundDrawList()->AddCircleFilled(center_, radius_, col, 0);
  } else {
    ImGui::GetBackgroundDrawList()->AddCircle(
        center_, radius_, col, 0, sty->width);
  }
  if (sty->text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(center_, col, sty->text.c_str());
}

ImVec2* Circle::center() { return &center_; }

void Circle::set_radius(const float r) { radius_ = r; }

}  // namesapce av
