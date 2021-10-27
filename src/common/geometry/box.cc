#include "box.h"

#include <cmath>

namespace av {

bool IsOverlap(const Box& a, const Box& b) {
  return std::min(a.rt.x, b.rt.x) > std::max(a.lb.x, b.lb.x) &&
         std::min(a.rt.y, b.rt.y) > std::max(a.lb.y, b.lb.y);
}

bool IsPointInBox(const Point2d& p, const Box& b) {
  return p.x > b.lb.x && p.x < b.rt.x && p.y > b.lb.y && p.y < b.rt.y;
}

}  // namespace av
