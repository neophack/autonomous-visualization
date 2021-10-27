/// Helper functions
#pragma once

#include "point.h"
#include "box.h"
#include "config.h"

namespace av {
namespace feature {

Box GetViewBox(const MainView& view);

Point2d To2d(const Point3d& p);

Point2d ToGuiView(const Point2d& p, const MainView& view);

}  // namespace feature
}  // namespace av
