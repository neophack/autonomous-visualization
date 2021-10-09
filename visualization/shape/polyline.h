/// Define the circle shape
#pragma once

#include "shape.h"
#include <vector>

/// namespace
namespace av {

class PolyLine final : public Shape {
 public:
  PolyLine() = default;
  /// Constructor with center and radius
  explicit PolyLine(const std::vector<ImVec2>& pts);
  /// Constructor with center and radius and style
  PolyLine(const std::vector<ImVec2>& pts, const Style& style);
  virtual ~PolyLine() = default;

  /// Get center pointer
  std::vector<ImVec2>* points();

  /// Draw the circle
  void Draw() override;

 private:
  std::vector<ImVec2> points_{};
};

};  // namespace av
