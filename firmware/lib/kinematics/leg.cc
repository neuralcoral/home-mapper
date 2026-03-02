#include "../kinematics/leg.h"

Link::Link(const float& length,
           const float& initial_theta,
           const int& servo_pin): length(length), initial_theta(initial_theta)
{
    current_theta = initial_theta;
    servo = Servo();
    servo.attach(servo_pin);
}

Leg::Leg(const Link& tibia, const Link& femur) : tibia(tibia), femur(femur) {}

void Link::setup()
{
    servo.write(initial_theta);
}


void Leg::setup()
{
    tibia.setup();
    femur.setup();
}

void step(const Coordinate& coordinate)
{

}
