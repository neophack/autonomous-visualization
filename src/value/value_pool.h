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
  /// Constructor
  ValuePool() = default;
  /// Disable copy constructor
  ValuePool(const ValuePool&) = delete;
  /// Disable assignment operator
  ValuePool& operator=(const ValuePool&) = delete;
  /// Default move constructor
  ValuePool(ValuePool&&) = default;
  /// Default move operator
  ValuePool& operator=(ValuePool&&) = default;

  /// Update state of a value
  void UpdateValue(const std::string& id, const double value);
  /// Get latest value of a value
  double GetValue(const std::string& id);
  /// Get all value ids with no param
  std::vector<std::string> GetAllValueIds();

 private:
  std::unordered_map<std::string, double> id_value_{};
  std::size_t value_limit_{100};
};


}  // namespace av
