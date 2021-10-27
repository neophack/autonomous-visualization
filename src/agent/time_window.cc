#include "time_window.h"

namespace av {

TimeWindow::TimeWindow(const std::size_t cap, const double period)
  : capacity_{cap}, time_period_{period} {}

void TimeWindow::UpdateIdAndTime(const std::string id, const double time) {
  if (!id_time_.count(id)) id_time_[id] = {.id = id};
  id_time_[id].time = time;
  ToHead(&id_time_[id]);

  // Trim the length
  while (id_time_.size() > capacity_) {
    out_ids_.push_back(time_tail_->id);
    time_tail_ = time_tail_->prev;
    id_time_.erase(time_tail_->next->id);
    time_tail_->next = nullptr;
  }
}

std::vector<std::string> TimeWindow::GetIdsInWindow() {
  return GetIdsInTime(time_period_);
}

std::vector<std::string> TimeWindow::GetIdsInTime(const double t) {
  auto node = time_head_;
  std::vector<std::string> res;
  while (node && time_head_->time - node->time < t) {
    res.push_back(node->id);
    node = node->next;
  }

  return res;  // RVO
}

std::vector<std::string> TimeWindow::GetIdsOutWindow() {
  while (time_tail_ && time_head_->time - time_tail_->time > time_period_) {
    out_ids_.push_back(time_tail_->id);
    time_tail_ = time_tail_->prev;
    time_tail_->next = nullptr;
    id_time_.erase(out_ids_.back());
  }

  std::vector<std::string> res;
  std::swap(res, out_ids_);
  return res;
}

void TimeWindow::ToHead(Node* node) {
  if (!node || node == time_head_) return;
  if (node == time_tail_) time_tail_ = time_tail_->prev;
  if (node->prev) node->prev->next = node->next;
  if (node->next) node->next->prev = node->prev;

  node->prev = nullptr;
  node->next = time_head_;
  if (time_head_) time_head_->prev = node;
  time_head_ = node;
  if (!time_tail_) time_tail_ = time_head_;
}

void TimeWindow::Clear() {
  time_head_ = nullptr;
  time_tail_ = nullptr;
  out_ids_.clear();
  id_time_.clear();
}

}  // namespace
