/// Define the adapter interface to adapt different map format
#pragma once

#include "map_graph.h"

#include <string>

/// namespace av
namespace av {

/// Interface class for all adapter
class MapAdapter {
 public:
  virtual MapGraph InitMap(const std::string& path) const = 0;
};

}  // namespace av
