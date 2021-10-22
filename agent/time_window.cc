#include "time_window.h"

namespace av {

TimeWindow::TimeWindow(const std::size_t cap, const double period)
  : capacity_{cap}, time_period_{period} {}

void TimeWindow::UpdateIdAndTime(const std::string id, const double time) {
  if (!id_time_.count(id)) id_time_[id] = {.id = id, .time = time};
  ToHead(&id_time_[id]);

  // Trim the length
  while (id_time_.size() > capacity_) {
    time_tail_ = time_tail_->prev;
    id_time_.erase[time_tail_->next.id];
    time_tail_->next = nullptr;
  }
}

std::vector<std::string> TimeWindow::GetIdsInWindow() {
  return GetIdsInTime(time_period_);
}

std::vector<std::string> TimeWindow::GetIdsInTime(const double t) {
  auto node = time_head_;
  std::vector<std::string> res
  while (node && time_head_->time - node_->time < t) {
    res.push_back(node->id);
    node = node->next;
  }

  return res;  // RVO
}

std::vector<std::string> TimeWindow::GetIdsOutWindow() {
  auto node = time_tail_;
  std::vector<std::string> res
  while (node && time_head_->time - node->time > time_period_) {
    res.push_back(node->val);
    node = node->prev;
    node->next = nullptr;
    id_time_.erase(res.back());
  }
}

void TimeWindow::ToHead(Node* node) {
  if (!node || node == time_head_) return;
  if (!time_head_ && !time_tail_) {
    time_head_ = node;
    time_tail_ = node;
    return;
  }

  if (node == time_tail_) time_tail_ = time_head_->prev;
  if (node->prev) node->prev->next = node->next;
  if (node->next) node->next->prev = node->prev;
  node->prev = nullptr;
  node->next = time_head_;
  time_head_->prev = node;
  time_head_ = node;
}

}  // namespace
