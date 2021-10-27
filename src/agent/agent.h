/// Define the agent class
#pragma once

#include <deque>
#include "state.h"

/// namespace
namespace av {

/// All moving objects are agents
class Agent {
 public:
  /// Default constructor
  Agent() = default;
  /// Copy constructor
  Agent(const Agent&);
  /// Assignment operator
  Agent& operator=(const Agent&);

  /// Only init with size and right value of state
  Agent(std::size_t, State&&);
  /// Only init with right value of state
  Agent(State&&);
  /// Update state
  void Update(State&&);
  /// Get id
  const std::string& GetId() const;
  /// Get latest state
  State* GetLatestState();
  /// Get history
  std::deque<State>* GetHistory();

 private:
  std::size_t history_size_{100};
  std::string id_{};
  std::deque<State> history_{};
};

}  // namespace av
