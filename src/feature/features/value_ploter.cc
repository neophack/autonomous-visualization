#include "value_ploter.h"

#include <iostream>
#include <unordered_map>
#include <cmath>

#include "implot.h"

namespace av {

struct ScrollingBuffer {
  std::size_t max_size{2000};
  std::size_t offset{0};
  std::vector<ImVec2> data;

  ScrollingBuffer() { data.reserve(max_size); }

  void AddPoint(float x, float y) {
    if (data.size() < max_size) {
      data.push_back(ImVec2(x,y));
    } else {
      data[offset] = ImVec2(x,y);
      offset = (offset + 1) % max_size;
    }
  }
};

ValuePloter::ValuePloter(ValuePool* vp) : values_{vp} {}

void ValuePloter::Execute(Config* conf) {
  if (!ImGui::CollapsingHeader("Value Viewer")) return;

  // Start plot in a new window
  ImGui::Begin("Value Ploter");
  ImGui::BulletText("All values catched by value pool are ploted.");
  ImPlot::CreateContext();

  static std::unordered_map<std::string, ScrollingBuffer> buffs{};
  static float t = 0;
  t += ImGui::GetIO().DeltaTime;

  for (auto& id : values_->GetAllValueIds()) {
    buffs[id].AddPoint(t, values_->GetValue(id));
  }

  if (ImPlot::BeginPlot("##RealTime")) {
    ImPlot::SetupAxisLimits(ImAxis_X1, t - 10.0, t, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, -1, 1);
    for (auto& [id, buff] : buffs) {
      ImPlot::PlotLine(id.c_str(), &buff.data[0].x, &buff.data[0].y,
          buff.data.size(), buff.offset, 2 * sizeof(float));
    }
    ImPlot::EndPlot();
  }

  ImGui::End();
}

}  // namespace av
