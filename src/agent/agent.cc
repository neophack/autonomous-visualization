#include "agent.h"

#include <algorithm>

namespace av {

Agent::Agent(const Agent& rhs)
    : history_size_{rhs.history_size_}, id_{rhs.id_}, history_{rhs.history_} {}

Agent& Agent::operator=(const Agent& rhs) {
  if (&rhs == this) return *this;
  this->history_size_ = rhs.history_size_;
  this->id_ = rhs.id_;
  this->history_ = rhs.history_;
  return *this;
}

Agent::Agent(std::size_t size, State&& s) : history_size_{size}, id_{s.id} {
  history_.push_front(std::move(s));
}

Agent::Agent(State&& s) : id_{s.id} {
  history_.push_front(std::move(s));
}

void Agent::Update(State&& s) {
  history_.push_front(std::move(s));
  while (history_.size() > history_size_) history_.pop_back();
}

const std::string& Agent::GetId() const { return id_; }

State* Agent::GetLatestState() { return &history_.front(); }

std::deque<State>* Agent::GetHistory() { return &history_; }

}  // namespace av
