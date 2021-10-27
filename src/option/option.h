/// Define all option interface
#pragma once

#include "config.h"

namespace av {

class Option {
 public:
  virtual void Update(Config*) = 0;
};

}  // namespace av
