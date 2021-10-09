/// Define the circle shape
#pragma once

#include "shape.h"
#include <vector>

/// namespace
namespace av {

/// Define the polygon shape
class Polygon final : public Shape {
 public:
  Polygon() = default;
  /// Constructor with center and radius
  explicit Polygon(const std::vector<ImVec2>& pts);
  /// Constructor with center and radius and style
  Polygon(const std::vector<ImVec2>& pts, const Style& style);
  virtual ~Polygon() = default;

  /// Get center pointer
  std::vector<ImVec2>* points();

  /// Draw the circle
  void Draw() override;

 private:
  /// Points must be in clockwise order
  /// Tow points for rectangular up-left and right-bottom points
  /// Three points for triangular in clockwise order
  /// Four points for quad poly in clockwise order
  /// more points will draw a filled shape
  std::vector<ImVec2> points_{};
};

};  // namespace av
