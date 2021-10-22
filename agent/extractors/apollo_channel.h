/// Define the class to extract state from apollo channel
#pragma once

#include "state_extractor.h"

#include "cyber.h"

#include "localization_pose.pb.h"
#include "perception_obstacle.pb.h"
#include "planning.pb.h"
#include "prediction_obstacles.pb.h"

namespace av {

/// Extract state from apollo channel
class ApolloChannel final : public StateExtractor {
 public:
  ApolloChannel();
  std::vector<State> ExtractStates() override;

 private:
  std::vector<State> ExtractPerceptionStates(const PerceptionObstacles& msg);
  std::unordered_map<std::string, stf::vector<Trajectory>>
  ExtractPredictionFutures(const PredictionObstacles& msg);
  State ExtractLocalizationState(const LocalizationEstimate& msg);
  std::vector<Trajectory> ExtractPlanningFutures(const ADCTrajectory& msg);

 private:
  std::shared_ptr<neodrive::cyber::Node> node_;
  std::shared_ptr<neodrive::cyber::Reader<
      neodrive::global::localization::LocalizationEstimate>> reader_loc_{};
  std::shared_ptr<neodrive::cyber::Reader<
      neodrive::global::perception::PerceptionObstacles>> reader_per_{};
  std::shared_ptr<neodrive::cyber::Reader<
      neodrive::global::planning::ADCTrajectory>> reader_pln_{};
  std::shared_ptr<neodrive::cyber::Reader<
      neodrive::global::prediction::PredictionObstacles>> reader_prd_{};
};




}  // namespace av
