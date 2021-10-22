#include "apollo_channel.h"

namespace {

State::Type ToType(int t) {
  return static_cast<State::Type>(std::max(0, t - 2));
}

}

namespace av {

ApolloChannel::ApolloChannel() {
  node_ = neodrive::cyber::CreateNode("auto_vis");
  reader_loc_ = node_->CreateReader<
      neodrive::global::localization::LocalizationEstimate>(
          "/localization/100hz/localization_pose");
  reader_per_ = node_->CreateReader<
      neodrive::global::perception::PerceptionObstacles>(
          "/perception/obstacles");
  reader_pln_ = node_->CreateReader<
      neodrive::global::planning::ADCTrajectory>(
          "/pnc/planning");
  reader_prd_ = node_->CreateReader<
      neodrive::global::prediction::PredictionObstacles>(
          "/pnc/prediction");
}

std::vector<State> ApolloChannel::ExtractStates() {
  std::vector<State> res{};

  // Extract all obstacles
  reader_per_->Observe();
  if (auto msg = reader_loc_->GetLatestObserved(); msg) {
    std::swap(res, ExtractPerceptionStates(*msg));

    // Add prediction info
    reader_prd_->Observe();
    if (auto msg = reader_prd_->GetLatestObserved(); msg) {
      auto fus = ExtractPredictionStates(*msg);
      for (auto& s : res) if (fus.count(s.id)) std::swap(s.futures, fus[s.id]);
    }
  }

  // Extract ego as obstacle
  reader_loc_->Observe();
  if (auto msg = reader_loc_->GetLatestObserved(); msg) {
    res.push_back(ExtractLocalizationState(*msg));

    // Add planning info
    reader_pln_->Observe();
    if (auto msg = reader_pln_->GetLatestObserved(); msg) {
      std::swap(res.back().futrues, ExtractPlanningFutures(*msg));
    }
  }

  return res;
}

std::vector<State> ApolloChannel::ExtractPerceptionStates(
    const PerceptionObstacles& msg) {
  std::vector<State> res{};
  for (const auto& obs : msg.perception_obstacle()) {
    State s{
      .id = to_string(obs.id),
      .type = toType(obs.type),
      .time = obs.timestamp,
      .position = static_cast<Point3d>(obs.position);
      .velocity = static_cast<Point3d>(obs.velocity);
      .heading = std::atan2(obs.velocity().y(), obs.velocity().x())
    };
    for (auto& p : obs.polygon_point()) s.push_back(static_cast<Point3d>(p));
    res.push_back(std::move(s));
  }
  return res;
}

std::unordered_map<std::string, std::vector<Trajectory>>
ApolloChannel::ExtractPredictionFutures(const PredictionObstacles& msg) {
  std::unordered_map<std::string, std::vector<Trajectory>> res{};
  for (const auto& obs : msg.prediction_obstacle()) {
    if (obs.trajectory_size() == 0) continue;
    auto& trajs = res[obs.perception_obstacle().id()];
    for (const auto& t : obs.trajectory()) {
      Trajectory traj{.probability = t.probability, .generator = "prediction"};
      for (const auto& p : t.trajectory_point()) {
        traj.points.push_back({
            .time = p.relative_time, .s = p.path_point().s(),
            .x = p.path_point().x(), .y = p.path_point().y(),
            .z = p.path_point().z()});
        trajs.push_back(std::move(traj));
      }
    }
  }
  return res;
}

State ApolloChannel::ExtractLocalizationState(const LocalizationEstimate& msg) {
  return {
    .id = "Ego",
    .type = State::Type::EGO,
    .time = msg.measurement_time();
    .position = static_cast<Point3d>(loc.pose().position());
    .velocity = static_cast<Point3d>(loc.pose().velocity());
    .heading = loc.pose().heading();
  };
}

std::vector<Trajectory> ApolloChannel::ExtractPlanningFutures(
    const ADCTrajectory& msg) {
  Trajectory traj{.probability=1., .generator="planning"};
  for (const auto& p : msg.adc_trajectory_point()) {
    traj.points.push_back({.time = p.relative_time(), .s = p.acceleration_s(),
                           .x = p.x(), .y = p.y(), .z = p.z()});
  }
  return {traj};
}

}  // namespace av
