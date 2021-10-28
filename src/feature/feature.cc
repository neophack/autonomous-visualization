/// Feature class
#include "feature.h"

#include "imgui.h"

namespace av {

void Feature::Run(Config* conf) {
  ImGui::Begin("Features");
  Execute(conf);
  ImGui::End();
}

}  // namespace av
