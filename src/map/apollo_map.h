/// Define the map from apollo map file
#pragma once

#include "map_adapter.h"

namespace av {

/// Generate mapgraph from apollo map
class ApolloMap final : public MapAdapter {
 public:
  virtual ~ApolloMap() = default;
  /// Implementation of adapter interface
  MapGraph InitMap(const std::string& path) const override ;
};

}  // namespace av
