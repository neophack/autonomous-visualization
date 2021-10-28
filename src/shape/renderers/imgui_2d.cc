#include "imgui_2d.h"

#include "imgui.h"

#include <iostream>

namespace av {

namespace {

ImU32 ToColor(const Color& c) { return IM_COL32(c.r, c.g, c.b, c.a); }

ImVec2 ToVec2(const Point2d& p) {
  return {static_cast<float>(p.x), static_cast<float>(p.y)};
}

}

void Imgui2d::Draw(const Circle& obj) {
  const auto& sty = obj.style;
  auto col = ToColor(sty.color);

  auto center = ToVec2(obj.center);

  if (obj.style.is_fill) {
    ImGui::GetBackgroundDrawList()->AddCircleFilled(center, obj.radius, col, 0);
  } else {
    ImGui::GetBackgroundDrawList()->AddCircle(
        center, obj.radius, col, 0, obj.style.width);
  }
  if (obj.style.text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(center, col, sty.text.c_str());
}

void Imgui2d::Draw(const Polygon& obj) {
  auto col = ToColor(obj.style.color);
  const auto& sty = obj.style;
  std::vector<ImVec2> pts{};
  for (const auto& p : obj.points) { pts.emplace_back(p.x, p.y); }

  if (sty.is_fill) {
    ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(
        pts.data(), pts.size(), col);
  } else {
    pts.push_back(pts.front());
    ImGui::GetBackgroundDrawList()->AddPolyline(
        pts.data(), pts.size(), col, 0, sty.width);
    pts.pop_back();
  }
  if (sty.text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(pts.front(), col, sty.text.c_str());
}

void Imgui2d::Draw(const Polyline& obj) {
  auto col = ToColor(obj.style.color);
  const auto& sty = obj.style;
  std::vector<ImVec2> pts{};
  for (const auto& p : obj.points) { pts.emplace_back(p.x, p.y); }

  ImGui::GetBackgroundDrawList()->AddPolyline(
      pts.data(), pts.size(), col, 0, sty.width);
  if (sty.text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(pts.front(), col, sty.text.c_str());
}

void Imgui2d::Draw(const Quadrilateral& obj) {
  auto col = ToColor(obj.style.color);
  const auto& sty = obj.style;
  auto p0 = ToVec2(obj.points[0]);
  auto p1 = ToVec2(obj.points[1]);
  auto p2 = ToVec2(obj.points[2]);
  auto p3 = ToVec2(obj.points[3]);

  if (sty.is_fill) {
    ImGui::GetBackgroundDrawList()->AddQuadFilled(p0, p1, p2, p3, col);
  } else {
    ImGui::GetBackgroundDrawList()->AddQuad(p0, p1, p2, p3, col, sty.width);
  }
  if (sty.text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(p0, col, sty.text.c_str());
}

void Imgui2d::Draw(const Rectangle& obj) {
  auto col = ToColor(obj.style.color);
  const auto& sty = obj.style;
  auto lt = ToVec2(obj.points[0]);
  auto rb = ToVec2(obj.points[1]);

  if (sty.is_fill) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(lt, rb, col);
  } else {
    ImGui::GetBackgroundDrawList()->AddRect(lt, rb, col, 0., 0, sty.width);
  }
  if (sty.text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(lt, col, sty.text.c_str());
}

void Imgui2d::Draw(const Triangle& obj) {
  auto col = ToColor(obj.style.color);
  const auto& sty = obj.style;
  auto p0 = ToVec2(obj.points[0]);
  auto p1 = ToVec2(obj.points[1]);
  auto p2 = ToVec2(obj.points[2]);

  if (sty.is_fill) {
    ImGui::GetBackgroundDrawList()->AddTriangleFilled(p0, p1, p2, col);
  } else {
    ImGui::GetBackgroundDrawList()->AddTriangle(p0, p1, p2, col, sty.width);
  }
  if (sty.text.empty()) return;
  ImGui::GetBackgroundDrawList()->AddText(p0, col, sty.text.c_str());
}

}  // namespace av
