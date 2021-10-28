#include "feature_helper.h"

#include <cmath>
#include <algorithm>

namespace av {
namespace feature {

Box GetViewBox(const MainViewConf& view) {
  double sin_h = std::sin(view.center.heading);
  double cos_h = std::cos(view.center.heading);
  Point2d cen{view.center.x, view.center.y};
  double half_w = view.width / 2;
  double half_h = view.height / 2;

  std::vector xs{
      half_w * cos_h + half_h * sin_h, half_w * cos_h - half_h * sin_h,
      -half_w * cos_h + half_h * sin_h, -half_w * cos_h - half_h * sin_h};
  std::vector ys{
      half_w * sin_h + half_h * cos_h, half_w * sin_h - half_h * cos_h,
      -half_w * sin_h + half_h * cos_h, -half_w * sin_h - half_h * cos_h};
  std::sort(xs.begin(), xs.end());
  std::sort(ys.begin(), ys.end());
  return {av::Point2d{xs.front(), ys.front()} * view.zoom_ratio + cen,
          av::Point2d{xs.back(), ys.back()} * view.zoom_ratio + cen};
}

Point2d To2d(const Point3d& p) { return {p.x, p.y}; }

Point2d ToGuiView(const Point2d& p, const MainViewConf& view) {
  auto res = p - Point2d{view.center.x, view.center.y};
  res = Rotate(res, view.center.heading);
  res /= view.zoom_ratio;
  res.y = -res.y + view.height / 2;
  res.x += view.width / 2;
  return res;
}

}  // namespace feature
}  // namespace av
