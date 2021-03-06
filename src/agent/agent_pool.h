/// Define the agent pool class
#pragma once

#include <unordered_map>
#include <string>

#include "state.h"
#include "agent.h"
#include "time_window.h"

namespace av {

/// Manage class for all agents
class AgentPool {
 public:
  /// Constructors
  AgentPool() = default;
  /// Disable copy constructor
  AgentPool(const AgentPool&) = delete;
  /// Disable assignment operator
  AgentPool& operator=(const AgentPool&) = delete;
  /// Default move constructor
  AgentPool(AgentPool&&) = default;
  /// Default move operator
  AgentPool& operator=(AgentPool&&) = default;

  /// Update state of an agent
  void Update(State&&);
  /// Get agent pointer by id
  Agent* GetAgent(const std::string& id);
  /// Get agent pointer by id
  Agent* operator[](const std::string& id);
  /// Get all agent ids
  std::vector<std::string> GetAllAgentIds();
  /// Get all agent ids in time
  std::vector<std::string> GetAgentIdsInTime(const double t);

 private:
  std::unordered_map<std::string, Agent> id_agent_{};
  TimeWindow time_window_{10000, 1.};
  double newest_time_{0.};
};

}  // namespace av
