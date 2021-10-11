/// Define the adapter interface to adapt different map format
#pragma once

#include "map_graph.h"

#include <string>

/// namespace av
namespace av {

/// Interface for all adapter
class MapAdapter {
 public:
  virtual MapGraph InitMap(const std::string& path) = 0;
};

}  // namespace av
