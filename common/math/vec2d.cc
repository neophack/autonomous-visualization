#include "vec2d.h"

#include <cmath>

namespace av {

Vec2d& operator+=(Vec2d& v, const double n) {
  v.x += n;
  v.y += n;
  return v;
}

Vec2d& operator-=(Vec2d& v, const double n) {
  v += -n;
  return v;
}

Vec2d& operator*=(Vec2d& v, const double n) {
  v.x *= n;
  v.y *= n;
  return v;
}

Vec2d& operator/=(Vec2d& v, const double n) {
  v.x /= n;
  v.y /= n;
  return v;
}

Vec2d operator+(const Vec2d& v1, const Vec2d& v2) {
  return {v1.x + v2.x, v1.y + v2.y};
}

Vec2d operator-(const Vec2d& v1, const Vec2d& v2) {
  return {v1.x - v2.x, v1.y - v2.y};
}

Vec2d operator*(const Vec2d& v, const double n) { return {v1.x * n, v1.y * n}; }

Vec2d operator/(const Vec2d& v, const double n) { return {v1.x / n, v1.y / n}; }

double operator*(const Vec2d& v1, const Vec2d& v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

double CrossProduct(const Vec2d& v1, const Vec2d& v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

double Length(const Vec2d& v) { return std::sqrt(v * v); }

double Angle(const Vec2d& v1, const Vec2d& v2) {
  return std::acos(v1 * v2 / Length(v1) / Length(v2));
}

Vec2d Rotate(const Vec2d& v, const double ang) {
  return {v.x * std::cos(ang) - v.y * std::sin(ang),
          v.x * std::sin(ang) + v.y * std::cos(ang)};
}

}  // namespace av
