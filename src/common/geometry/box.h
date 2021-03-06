/// Define the box class
#pragma once

#include "point.h"

namespace av {

struct Box {
  Point2d lb{};
  Point2d rt{};
};

bool IsOverlap(const Box& a, const Box& b);
bool IsPointInBox(const Point2d& p, const Box& b);

}  // namespace av
