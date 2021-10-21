#include "box.h"

#include <cmath>

namespace av {

bool IsOverlap(const Box& a, const Box& b) {
  return std::min(a.rt.x, b.rt.x) > std::max(a.lb.x, b.lb.x) &&
         std::min(a.rt.y, b.rt.y) > std::max(a.lb.y, b.lb.y);
}

}  // namespace av
