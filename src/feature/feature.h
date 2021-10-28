/// Define the all features' interface
#pragma once

#include "config.h"

namespace av {

class Feature {
 public:
  void Run(Config*);
  virtual void Execute(Config*) = 0;
};

} // namespace av
