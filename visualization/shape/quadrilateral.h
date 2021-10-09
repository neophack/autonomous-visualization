/// Define the circle shape
#pragma once

#include "shape.h"
#include <array>

/// namespace
namespace av {

/// Define the polygon shape
class Quadrilateral final : public Shape {
 public:
  Quadrilateral() = default;
  /// Constructor with center and radius
  explicit Quadrilateral(const std::array<ImVec2, 4>& pts);
  /// Constructor with center and radius and style
  Quadrilateral(const std::array<ImVec2, 4>& pts, const Style& style);
  virtual ~Quadrilateral() = default;

  /// Get center pointer
  std::array<ImVec2, 4>* points();

  /// Draw the circle
  void Draw() override;

 private:
  /// Points must be in clockwise order
  std::array<ImVec2, 4> points_{};
};

};  // namespace av
