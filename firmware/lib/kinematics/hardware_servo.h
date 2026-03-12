#ifndef HOME_MAPPER_HARDWARE_SERVO_H
#define HOME_MAPPER_HARDWARE_SERVO_H
#include "i_servo.h"
#include <Servo.h>
#include <Arduino.h>

class HardwareServo : public IServo {
    Servo servo;
    int pin;

public:
    explicit HardwareServo(const int& pin): pin(pin) {}
    void setup() override {
        servo.attach(pin);
    }
    void write(int angle) override {
        delay(50);
        servo.write(angle);
        delay(50);
    }
};

#endif //HOME_MAPPER_HARDWARE_SERVO_H
