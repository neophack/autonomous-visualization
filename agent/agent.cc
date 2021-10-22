#include "agent.h"

namespace av {

Agent::Agent(std::size_t size, State&& s) : history_size_{size}, id_{s.id} {
  history_size_.push_front(std::move(s));
}

void Agent::Update(State&& s) {
  history_.push_front(std::move(s));
  while (history_.size() > history_size_) history_size_.pop_back();
}

const std::string& Agent::GetId() const { return id_; }

State* Agent::GetLatestState() { return &history_.front(); }

std::deque<State>* Agent::GetLatestState() { return &history_; }

}  // namespace av
