/// Define the agent data extractor interface
#pragma once

#include "state.h"

#include <vector>

namespace av {

class StateExtractor {
 public:
  virtual std::vector<State> ExtractStates() = 0;
};


}  // namespace av
