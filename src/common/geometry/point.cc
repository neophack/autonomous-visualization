#include "point.h"
#include <cmath>

namespace av {

Point2d& operator+=(Point2d& p, const double n) {
  p.x += n;
  p.y += n;
  return p;
}

Point2d& operator-=(Point2d& p, const double n) {
  p += -n;
  return p;
}

Point2d& operator*=(Point2d& p, const double n) {
  p.x *= n;
  p.y *= n;
  return p;
}

Point2d& operator/=(Point2d& p, const double n) {
  p.x /= n;
  p.y /= n;
  return p;
}

Point2d operator+(const Point2d& p1, const Point2d& p2) {
  return {p1.x + p2.x, p1.y + p2.y};
}

Point2d operator-(const Point2d& p1, const Point2d& p2) {
  return {p1.x - p2.x, p1.y - p2.y};
}

Point2d operator*(const Point2d& p, const double n) { return {p.x * n, p.y * n}; }

Point2d operator/(const Point2d& p, const double n) { return {p.x / n, p.y / n}; }

Point2d Rotate(Point2d& p, const double ang) {
  return {p.x * std::cos(ang) - p.y * std::sin(ang),
          p.x * std::sin(ang) + p.y * std::cos(ang)};
}

}  // namespace av
