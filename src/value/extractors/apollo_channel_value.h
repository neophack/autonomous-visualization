/// Define the class to extract value from apollo channel
#pragma once

#include "value_extractor.h"

#include "cyber.h"
#include "control_cmd.pb.h"

namespace av {

/// Derived class to implement the value extrctor interface
class ApolloChannelValue final : public ValueExtractor {
 public:
  /// constructor
  ApolloChannelValue();
  /// Default virtual destructor
  virtual ~ApolloChannelValue() = default;

  /// Override interface to do extractings
  std::vector<std::pair<std::string, double>> ExtractValues() override;

 private:
  std::shared_ptr<neodrive::cyber::Node> node_;
  std::shared_ptr<neodrive::cyber::Reader<
      neodrive::global::control::ControlCommand>> reader_ctl_{};
};

}  // namespace av
