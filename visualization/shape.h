/// Define the interface for all shapes
#pragma once

#include <string>

#include "imgui.h"

/// namespace autonoumous visualization
namespace av {

/// Color struct
struct Color {
  int r{0};
  int g{0};
  int b{0};
  int a{0};
};

/// Render style
struct Style {
  Color color{0, 0, 0, 255};
  bool is_fill{false};
  std::string text{};
  float width{0.1};
};

// Shape interface for all shapes
class Shape {
 public:
  Shape() = default;
  /// Construct with style
  explicit Shape(const Style& style);
  /// Get the style struct
  Style* style();

 private:
  Style style_{};
};

}  // namespace av
