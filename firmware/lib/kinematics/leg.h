#ifndef HEXAPOD_LEG_H
#define HEXAPOD_LEG_H

#include <i_servo.h>
#include "coordinate.h"


struct GoalAngles {
    float coxa_angle;
    float femur_angle;
};
class Link
{
    const float length;
    const float initial_theta;
    float current_theta;

    IServo &servo;

public:
    Link(const float& length, const float& initial_theta, IServo& servo);
    void setup();
    void move(const float& goal_angle);
};

class Leg
{
    Link coxa;
    Link femur;
public:
    Leg(Link& coxa, Link& femur);

    void setup();
    void move(const GoalAngles& goal_angles);
};


#endif //HEXAPOD_LEG_H