#ifndef FIRMWARE_TRAJECTORY_PLANNER_H
#define FIRMWARE_TRAJECTORY_PLANNER_H

#include "leg.h"
#include "math.h"


struct LinkAngleLimits {
    float upper_bound, lower_bound;
};

struct LegAngleLimits {
    LinkAngleLimits coxa_link_limit, femur_link_limit;
};

class TrajectoryPlanner
{
    void handleSwing(Leg& leg, const LegAngleLimits& legAngleLimits, const float& phase);
    void handleStance(Leg& leg, const LegAngleLimits& legAngleLimits, const float& phase);
public:
    TrajectoryPlanner();
    void plan(Leg& leg, LegAngleLimits legAngleLimits, float phase);
};



#endif //FIRMWARE_TRAJECTORY_PLANNER_H
