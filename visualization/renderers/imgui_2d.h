/// 2d renderer
#pragma once

#include "renderer.h"
#include "shape.h"

namespace av {

/// Use Imgui 2d to render the shape
class Imgui2d final : public Renderer {
 public:
  void Draw(const Circle& obj);
  void Draw(const Polygon& obj);
  void Draw(const Polyline& obj);
  void Draw(const Quadrilateral& obj);
  void Draw(const Rectangle& obj);
  void Draw(const Triangle& obj);
};

}  // namespace av
