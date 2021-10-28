/// Define the class to extract value from apollo channel
#pragma once

#include "value_extractor.h"

#include "cyber.h"
#include "control_cmd.pb.h"

namespace av {

class ApolloChannelValue final : public ValueExtractor {
 public:
  ApolloChannelValue();
  virtual ~ApolloChannelValue() = default;

  std::vector<std::pair<std::string, double>> ExtractValues() override;

 private:
  std::shared_ptr<neodrive::cyber::Node> node_;
  std::shared_ptr<neodrive::cyber::Reader<
      neodrive::global::control::ControlCommand>> reader_ctl_{};
};

}  // namespace av
