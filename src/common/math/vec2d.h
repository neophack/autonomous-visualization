/// Define the 2d vector
#pragma once

namespace av {

struct Vec2d {
  double x{0.};
  double y{0.};
};

Vec2d& operator+=(Vec2d& v, const double n);
Vec2d& operator-=(Vec2d& v, const double n);
Vec2d& operator*=(Vec2d& v, const double n);
Vec2d& operator/=(Vec2d& v, const double n);

Vec2d operator+(const Vec2d& v1, const Vec2d& v2);
Vec2d operator-(const Vec2d& v1, const Vec2d& v2);
Vec2d operator*(const Vec2d& v, const double n);
Vec2d operator/(const Vec2d& v, const double n);

double operator*(const Vec2d& v1, const Vec2d& v2);
double CrossProduct(const Vec2d& v1, const Vec2d& v2);

double Length(const Vec2d& v);
double Angle(const Vec2d& v1, const Vec2d& v2);
Vec2d Rotate(const Vec2d& v, const double ang);

}  // namespace av
