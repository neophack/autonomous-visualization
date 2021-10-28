/// Define the value extractor interface
#pragma once

#include <vector>
#include <string>

namespace av {

/// An interface base class for all vlaue extractors
class ValueExtractor {
 public:
   /// Interface
   virtual std::vector<std::pair<std::string, double>> ExtractValues() = 0;
};

}  // namespace av
