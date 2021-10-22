/// Define the agent class
#pragma once

#include <deque>
#include "state.h"

/// namespace
namespace av {

/// All moving objects are agents
class Agent {
 public:
  /// Disable default constructor
  Agent() = delete;
  /// Disable copy constructor
  Agent(const Agent&) = delete;
  /// Disable copy operator
  Agent& operator=(const Agent&) = delete;

  /// Only init with size and right value of state
  Agent(std::size_t, State&&);
  /// Update state
  void Update(State&&);
  /// Get id
  const std::string& GetId() const;
  /// Get latest state
  State* GetLatestState();
  /// Get history
  std::deque<State>* GetHistory();

 private:
  const std::size_t history_size_{100}:
  const std::string id_{};
  std::deque<State> history_{}:
};

}  // namespace av
