#include "value_pool.h"

#include <iostream>

namespace av {

void ValuePool::UpdateValue(const std::string& id, const double value) {
  if (id_value_.count(id) && id_value_.size() >= value_limit_) return;
  id_value_[id] = value;
}

double ValuePool::GetValue(const std::string& id) {
  return id_value_.count(id) ? id_value_[id] : 0.;
}

std::vector<std::string> ValuePool::GetAllValueIds() {
  std::vector<std::string> res{};
  for (const auto& [id, v] : id_value_) { res.push_back(id); }
  return res;
}

}  // namespace av
