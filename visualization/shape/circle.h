/// Define the circle shape
#pragma once

#include "shape.h"

/// namespace
namespace av {

class Circle final : public Shape {
 public:
  /// Can not construct without center and radius
  Circle() = delete;
  /// Constructor with center and radius
  Circle(const ImVec2& c, const double r);
  /// Constructor with center and radius and style
  Circle(const ImVec2& c, const double r, const Style& style);
  virtual ~Circle() = default;

  /// Get center pointer
  ImVec2* center();
  /// Set radius
  void set_radius(const float r);

  /// Draw the circle
  void Draw() override;

 private:
  ImVec2 center_{0, 0};
  double radius_{0.1};
};

};  // namespace av
