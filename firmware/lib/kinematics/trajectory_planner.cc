#include "trajectory_planner.h"

TrajectoryPlanner::TrajectoryPlanner() {}

void TrajectoryPlanner::plan(Leg &leg, LegAngleLimits leg_angle_limits, float phase) {
    if (phase < 0.5) {
        handleSwing(leg, leg_angle_limits, phase);
    } else {
        handleStance(leg, leg_angle_limits, phase);
    }
}

float getCoxaSwing(const LinkAngleLimits& limits, const float& phase) {
    return 180.0 * sin(PI * phase);
}

float getFemurSwing(const LinkAngleLimits& limits, const float& phase) {
    return 90.0 * pow(2.0 * phase, 2.0);
}

void TrajectoryPlanner::handleSwing(Leg& leg, const LegAngleLimits& leg_angle_limits, const float& phase) {
    const float coxa_angle = getCoxaSwing(leg_angle_limits.coxa_link_limit, phase);
    const float femur_angle = getFemurSwing(leg_angle_limits.femur_link_limit, phase);

    const GoalAngles goal_angle { coxa_angle, femur_angle };
    leg.move(goal_angle);
}

float getCoxaStance(const LinkAngleLimits& limits, const float& phase) {
    return 180.0 * sin(PI * phase);
}

float getFemurStance(const LinkAngleLimits& limits, const float& phase) {
    if (phase < 0.9) {
        return limits.lower_bound;
    } else {
        return 90.0 * cos(HALF_PI * (phase - 0.9) / 0.1);
    }
}

void TrajectoryPlanner::handleStance(Leg& leg, const LegAngleLimits& leg_angle_limits, const float& phase) {
    const float coxa_angle = getCoxaStance(leg_angle_limits.coxa_link_limit, phase);
    const float femur_angle = getFemurStance(leg_angle_limits.femur_link_limit, phase);

    const GoalAngles goal_angle { coxa_angle, femur_angle };
    leg.move(goal_angle);
}