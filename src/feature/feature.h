/// Define the all features' interface
#pragma once

#include "config.h"

namespace av {

class Feature {
 public:
  virtual void Execute(Config*) = 0;
};

} // namespace av
