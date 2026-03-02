#ifndef HEXAPOD_LEG_H
#define HEXAPOD_LEG_H
#include <Servo.h>

#include "coordinate.h"

class Link
{
    const float length;
    const float initial_theta;

    float current_theta;
    Servo servo;
public:
    Link(const float& length, const float& initial_theta, const int& servo_pin);
    void setup();
};

class Leg
{
    Link tibia;
    Link femur;
public:
    Leg(const Link& tibia, const Link& femur);

    void setup();
    void step(const Coordinate& coordinate);
};


#endif //HEXAPOD_LEG_H