/// Define the point struct
#pragma once

namespace av {

struct Point2d {
  double x{0.};
  double y{0.};
};

struct Point3d {
  double x{0.};
  double y{0.};
  double z{0.};
};

Point2d& operator+=(Point2d& v, const double n);
Point2d& operator-=(Point2d& v, const double n);
Point2d& operator*=(Point2d& v, const double n);
Point2d& operator/=(Point2d& v, const double n);

Point2d operator+(const Point2d& v1, const Point2d& v2);
Point2d operator-(const Point2d& v1, const Point2d& v2);
Point2d operator*(const Point2d& v, const double n);
Point2d operator/(const Point2d& v, const double n);

Point2d Rotate(Point2d& p, const double ang);

}  // namespace av
