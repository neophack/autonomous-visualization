/// Define the circle shape
#pragma once

#include "shape.h"
#include <array>

/// namespace
namespace av {

/// Define the polygon shape
class Triangle final : public Shape {
 public:
  Triangle() = default;
  /// Constructor with center and radius
  explicit Triangle(const std::array<ImVec2, 3>& pts);
  /// Constructor with center and radius and style
  Triangle(const std::array<ImVec2, 3>& pts, const Style& style);
  virtual ~Triangle() = default;

  /// Get center pointer
  std::array<ImVec2, 3>* points();

  /// Draw the circle
  void Draw() override;

 private:
  /// Points must be in clockwise order
  std::array<ImVec2, 3> points_{};
};

};  // namespace av
