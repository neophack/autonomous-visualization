/// Define the circle shape
#pragma once

#include "shape.h"
#include <array>

/// namespace
namespace av {

/// Define the polygon shape
class Rectangle final : public Shape {
 public:
  Rectangle() = default;
  /// Constructor with center and radius
  explicit Rectangle(const std::array<ImVec2, 2>& pts);
  /// Constructor with center and radius and style
  Rectangle(const std::array<ImVec2, 2>& pts, const Style& style);
  virtual ~Rectangle() = default;

  /// Get center pointer
  std::array<ImVec2, 2>* points();

  /// Draw the circle
  void Draw() override;

 private:
  /// Points must be in clockwise order
  /// Tow points for rectangular up-left and right-bottom points
  /// Three points for triangular in clockwise order
  /// Four points for quad poly in clockwise order
  /// more points will draw a filled shape
  std::array<ImVec2, 2> points_{};
};

};  // namespace av
