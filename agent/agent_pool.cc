#include "agent_pool.h"

namespace av {

void AgentPool::Update(State&& s) {
  auto id = s.id;
  if (!id_agent_.count(id)) id_agent_.emplace(id, std::move(s));
  time_window_.UpdateIdAndTime(id, id_agent_[id].GetLatestState()->time);

  // Delete agent out time
  for (const auto& i : time_window_.GetIdsOutWindow()) id_agent_.erase(i);
}

Agent* AgentPool::GetAgent(const std::string& id) {
  return id_agent_.count(id) ? &id_agent_[id] : nullptr;
}

Agent* AgentPool::operator[](const std::string& id) {
  return GetAgent(id);
}

std::vector<std::string> AgentPool::GetAllAgentIds() {
  std::vector<std::string> res{};
  for (const auto& [id, agent] : id_agent_) { res.push_back(id); }
  return res;
}

std::vector<std::string> AgentPool::GetAgentIdsInTime(const double t) {
  return time_window_.GetIdsInTime(t);
}

}  // namespace av
