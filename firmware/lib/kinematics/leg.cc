#include "../kinematics/leg.h"

Link::Link(const float& length,
           const float& initial_theta,
           const int& servo_pin): length(length), initial_theta(initial_theta), servo_pin(servo_pin)
{
    current_theta = initial_theta;
}
void Link::safeWrite(const float &goal_angle) {
    delay(50);
    servo.write((int)goal_angle);
    delay(50);
}

void Link::setup()
{
    current_theta = initial_theta;
    safeWrite(current_theta);
    servo.attach(servo_pin);
}

void Link::move(const float &goal_angle) {
    safeWrite(goal_angle);
    current_theta = goal_angle;
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

