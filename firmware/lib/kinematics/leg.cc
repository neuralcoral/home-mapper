#include "leg.h"

Link::Link(const float& length,
           const float& initial_theta,
           IServo& servo): length(length), initial_theta(initial_theta), servo(servo)
{
    current_theta = initial_theta;
}

void Link::setup()
{
    current_theta = initial_theta;
    servo.write((int)current_theta);
}

void Link::move(const float &goal_angle) {
    current_theta = goal_angle;
    servo.write((int)goal_angle);
}


Leg::Leg(Link& coxa, Link& femur) : coxa(coxa), femur(femur) {}

void Leg::setup()
{
    coxa.setup();
    femur.setup();
}

void Leg::move(const GoalAngles &goal_angles) {
    coxa.move(goal_angles.coxa_angle);
    femur.move(goal_angles.femur_angle);
}

