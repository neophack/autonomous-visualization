#include "apollo_channel_agent.h"

#include <iostream>

namespace {

av::State::Type ToType(int t) {
  return static_cast<av::State::Type>(std::max(0, t - 2));
}

}

namespace av {

ApolloChannelAgent::ApolloChannelAgent() {
  neodrive::cyber::Init("apollo_channel");

  node_ = neodrive::cyber::CreateNode("av_agent");
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

std::vector<State> ApolloChannelAgent::ExtractStates() {
  std::cout << "Apollo channel agent ====================" << std::endl;
  std::vector<State> res{};

  // Extract all obstacles
  reader_per_->Observe();
  if (auto msg = reader_per_->GetLatestObserved(); msg) {
    std::cout << "receive perception" << std::endl;
    res = ExtractPerceptionStates(*msg);

    // Add prediction info
    reader_prd_->Observe();
    if (auto msg = reader_prd_->GetLatestObserved(); msg) {
      std::cout << "receive prediction" << std::endl;
      auto fus = ExtractPredictionFutures(*msg);
      for (auto& s : res) if (fus.count(s.id)) std::swap(s.futures, fus[s.id]);
    }
  }

  // Extract ego as obstacle
  reader_loc_->Observe();
  if (auto msg = reader_loc_->GetLatestObserved(); msg) {
    std::cout << "receive localization" << std::endl;
    auto state = ExtractLocalizationState(*msg);
    if (!res.empty()) state.time = res.back().time;
    res.push_back(state);

    // Add planning info
    reader_pln_->Observe();
    if (auto msg = reader_pln_->GetLatestObserved(); msg) {
      std::cout << "receive planning" << std::endl;
      res.back().futures = ExtractPlanningFutures(*msg);
    }
  }

  return res;
}

std::vector<State> ApolloChannelAgent::ExtractPerceptionStates(
    const neodrive::global::perception::PerceptionObstacles& msg) {
  std::vector<State> res{};
  if (msg.perception_obstacle_size() == 0) return res;
  const double time = msg.perception_obstacle().begin()->timestamp();
  for (const auto& obs : msg.perception_obstacle()) {
    State s{
      .id = std::to_string(obs.id()),
      .type = ToType(obs.type()),
      .time = time,
      .position = {obs.position().x(), obs.position().y(), obs.position().z()},
      .velocity = {obs.velocity().x(), obs.velocity().y(), obs.velocity().z()},
      .heading = std::atan2(obs.velocity().y(), obs.velocity().x())
    };
    for (auto& p : obs.polygon_point()) s.shape.push_back({
        p.x(), p.y(), p.z()});
    res.push_back(std::move(s));
  }
  return res;
}

std::unordered_map<std::string, std::vector<Trajectory>>
ApolloChannelAgent::ExtractPredictionFutures(
    const neodrive::global::prediction::PredictionObstacles& msg) {
  std::unordered_map<std::string, std::vector<Trajectory>> res{};
  for (const auto& obs : msg.prediction_obstacle()) {
    if (obs.trajectory_size() == 0) continue;
    auto& trajs = res[std::to_string(obs.perception_obstacle().id())];
    for (const auto& t : obs.trajectory()) {
      Trajectory traj{.probability = t.probability(),
                      .generator = "prediction"};
      for (const auto& p : t.trajectory_point()) {
        traj.points.push_back(Waypoint{
            .time = p.relative_time(), .s = p.path_point().s(),
            .x = p.path_point().x(), .y = p.path_point().y(),
            .z = p.path_point().z()});
      }
      trajs.push_back(std::move(traj));
    }
  }
  return res;
}

State ApolloChannelAgent::ExtractLocalizationState(
    const neodrive::global::localization::LocalizationEstimate& msg) {
  std::vector<Point3d> shape{};
  State res{
    .id = "Ego",
    .type = State::Type::VEHICLE,
    .time = msg.measurement_time(),
    .position = {msg.pose().position().x(), msg.pose().position().y(),
                 msg.pose().position().z()},
    .velocity = {msg.pose().linear_velocity().x(),
                 msg.pose().linear_velocity().y(),
                 msg.pose().linear_velocity().z()},
  };
  const auto& o = msg.pose().orientation();
  res.heading = std::atan2(2.0 * o.qw() * o.qz() + o.qx() * o.qy(),
                           1.0 - 2.0 * (o.qy() * o.qy() + o.qz() * o.qz())) +
                3.1415 / 2.;

  // set shape
  double half_w = 1.0 / 2.;
  double half_h = 2.87 / 2.;
  std::vector<Point3d> pts{{-half_h, half_w}, {half_h, half_w},
                           {half_h, -half_w}, {-half_h, -half_w}};
  double sin_h = std::sin(res.heading);
  double cos_h = std::cos(res.heading);
  for (auto p : pts) {
    res.shape.push_back({p.x * cos_h - p.y * sin_h + res.position.x,
                         p.x * sin_h + p.y * cos_h + res.position.y});
  }
  return res;
}

std::vector<Trajectory> ApolloChannelAgent::ExtractPlanningFutures(
    const neodrive::global::planning::ADCTrajectory& msg) {
  Trajectory traj{.probability=1., .generator="planning"};
  for (const auto& p : msg.adc_trajectory_point()) {
    traj.points.push_back({.time = p.relative_time(), .s = p.acceleration_s(),
                           .x = p.x(), .y = p.y(), .z = p.z()});
  }
  return {traj};
}

}  // namespace av
