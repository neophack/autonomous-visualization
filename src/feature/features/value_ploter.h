/// Plot values
#pragma once

#include "feature.h"
#include "value_pool.h"

namespace av {

/// Tool to plot values
class ValuePloter final : public Feature {
 public:
  /// Disable default constructor
  ValuePloter() = delete;
  /// Default virtual destructor
  virtual ~ValuePloter() = default;
  /// Can only construct with vlaue pool pointer
  explicit ValuePloter(ValuePool* vp);
  /// Implementation of feature interface
  void Execute(Config* conf) override;

 private:
  ValuePool* values_{nullptr};
};

}  // namesapce av
