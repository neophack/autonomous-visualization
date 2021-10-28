/// Define the agent data extractor interface
#pragma once

#include "state.h"

#include <vector>

namespace av {

/// The interface class for all agent extractors
class AgentExtractor {
 public:
  /// Extact interface
  virtual std::vector<State> ExtractStates() = 0;
};


}  // namespace av
