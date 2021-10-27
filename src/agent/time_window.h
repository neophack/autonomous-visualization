/// Define time window class
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace av {

/// Manage all ids in time window
class TimeWindow {
 public:
  /// Delete default constructor
  TimeWindow() = delete;
  /// Can only use period to construct the instance
  TimeWindow(const std::size_t cap, const double period);

  /// Insert id and time to window
  void UpdateIdAndTime(const std::string id, const double time);
  /// Get all ids within window
  std::vector<std::string> GetIdsInWindow();
  /// Get all ids in time
  std::vector<std::string> GetIdsInTime(const double t);
  /// Get all ids out window, this will release all ids out the window
  std::vector<std::string> GetIdsOutWindow();
  /// clear all states
  void Clear();

 private:
  struct Node {
    std::string id{};
    double time{0.};
    Node* prev{nullptr};
    Node* next{nullptr};
  };

  void ToHead(Node*);

  const std::size_t capacity_{1000};
  const double time_period_{0.5};
  Node* time_head_{nullptr};
  Node* time_tail_{nullptr};
  std::vector<std::string> out_ids_{};

  std::unordered_map<std::string, Node> id_time_{};
};


}  // namespace av
