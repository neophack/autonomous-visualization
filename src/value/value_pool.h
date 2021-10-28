/// Define the value pool class
#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "value.h"

namespace av {

/// Manage all agents
class ValuePool {
 public:
  /// Constructors ValuePool() = default;
  ValuePool() = default;
  ValuePool(const ValuePool&) = delete;
  ValuePool& operator=(const ValuePool&) = delete;
  ValuePool(ValuePool&&) = default;
  ValuePool& operator=(ValuePool&&) = default;

  /// Update states
  void UpdateValue(const std::string& id, const double value);
  /// Get latest value
  double GetValue(const std::string& id);
  std::vector<std::string> GetAllValueIds();

 private:
  std::unordered_map<std::string, double> id_value_{};
  std::size_t value_limit_{100};
};


}  // namespace av
