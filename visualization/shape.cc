#include "shape.h"

namespace av {

Shape::Shape(const Style& style) : style_{style} {}

Style* Shape::style() { return &style_; }

}  // namespace av
