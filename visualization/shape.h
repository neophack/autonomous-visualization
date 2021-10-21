/// Define the interface for all shapes
#pragma once

#include <string>
#include <vector>
#include <array>

#include "point.h"

/// namespace autonoumous visualization
namespace av {

/// Color struct
struct Color {
  unsigned char r{0};  // 0-255
  unsigned char g{0};
  unsigned char b{0};
  unsigned char a{0};
};

/// Render style
struct Style {
  Color color{0, 0, 0, 255};
  bool is_fill{false};
  std::string text{};
  float width{0.1};
};

/// Circle
struct Circle {
  Style style{};

  Point2d center{0, 0};
  double radius{0.1};
};

/// Polygon 
struct Polygon {
  Style style{};

  /// Points must be in clockwise order
  std::vector<Point2d> points{};
};

/// Polyline
struct Polyline {
  Style style{};

  std::vector<Point2d> points{};
};

/// Quadrilateral
struct Quadrilateral {
  Style style{};

  /// Points must be in clockwise order
  std::array<Point2d, 4> points{};
};

/// Rectangle
struct Rectangle {
  Style style{};

  /// left-up and right-bottom point
  std::array<Point2d, 2> points{};
};

/// Triangle
struct Triangle {
  Style style{};

  /// Points must be in clockwise order
  std::array<Point2d, 3> points{};
};


}  // namespace av
