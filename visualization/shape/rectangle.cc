#include "rectangle.h"

namespace av {

Rectangle::Rectangle(const std::array<ImVec2, 2>& pts) : points_{pts} {}

Rectangle::Rectangle(const std::array<ImVec2, 2>& pts, const Style& stye)
    : Shape(stye), points_{pts} {}

std::array<ImVec2, 2>* Rectangle::points() { return &points_; }

void Rectangle::Draw() {
  auto sty = Shape::style();
  auto col = IM_COL32(sty->color.r, sty->color.g, sty->color.b, sty->color.a);
  auto [lt, rb] = points_;
  if (sty->is_fill) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(lt, rb, col);
  } else {
    ImGui::GetBackgroundDrawList()->AddRect(lt, rb, col, 0., 0, sty->width);
  }
  if (sty->text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(lt, col, sty->text.c_str());
}

}  // namesapce av
