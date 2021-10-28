/// Define the 1d data
#pragma once

#include <string>
#include <deque>

namespace av {

/// A realtime value with name
struct Value {
  std::string id{};

  double val{0.};
};

/// A value list with name and length limit
struct Value1d {
  std::string id{};
  std::size_t history_size{100};

  std::deque<double> history{};
};

}  // namespace av
