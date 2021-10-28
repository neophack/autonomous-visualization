#include "apollo_channel_value.h"

#include <iostream>

namespace av {

ApolloChannelValue::ApolloChannelValue() {
  neodrive::cyber::Init("apollo_channel");
  node_ = neodrive::cyber::CreateNode("av_value");
  reader_ctl_ = node_->CreateReader<
      neodrive::global::control::ControlCommand>("/pnc/control");
}

std::vector<std::pair<std::string, double>>
ApolloChannelValue::ExtractValues() {
  std::cout << "Apollo channel value ====================" << std::endl;
  std::vector<std::pair<std::string, double>> res{};

  reader_ctl_->Observe();
  if (auto msg = reader_ctl_->GetLatestObserved(); msg) {
    std::cout << "Receive control msg" << std::endl;
    res.emplace_back("throttle", msg->throttle());
    res.emplace_back("brake", msg->brake());
    res.emplace_back("target_speed", msg->speed());
  }

  return res;  // RVO
}

}  // namespace
