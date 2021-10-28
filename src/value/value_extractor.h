/// Define the value extractor interface
#pragma once

#include <vector>
#include <string>

namespace av {

class ValueExtractor {
 public:
   virtual std::vector<std::pair<std::string, double>> ExtractValues() = 0;
};

}  // namespace av
