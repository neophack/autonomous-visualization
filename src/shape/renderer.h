/// Define the render interface
#pragma once
#include "shape.h"

namespace av {

class Renderer {
 public:
  virtual void Draw(const Circle&) = 0;
  virtual void Draw(const Polygon&) = 0;
  virtual void Draw(const Polyline&) = 0;
  virtual void Draw(const Quadrilateral&) = 0;
  virtual void Draw(const Rectangle&) = 0;
  virtual void Draw(const Triangle&) = 0;
};

}  // namespace av
