#include <Arduino.h>
#include <Servo.h>

#include "../lib/kinematics/leg.h"
#include "../lib/tools/calibration_tool.h"

#define TIBIA_LENGTH 6.0
#define FEMUR_LENGTH 4.0

// Front Left
#define FEMUR_1_PIN 3
#define TIBIA_1_PIN 2
#define FEMUR_1_THETA 90.0
#define TIBIA_1_THETA 100.0

// Front Right
#define FEMUR_2_PIN 9
#define TIBIA_2_PIN 8
#define FEMUR_2_THETA 90.0
#define TIBIA_2_THETA 90.0

// Center Left
#define FEMUR_3_PIN 5
#define TIBIA_3_PIN 4
#define FEMUR_3_THETA 90.0
#define TIBIA_3_THETA 85.0

// Center Right
#define FEMUR_4_PIN 11
#define TIBIA_4_PIN 10
#define FEMUR_4_THETA 100.0
#define TIBIA_4_THETA 82.0

// Back Left
#define FEMUR_5_PIN 7
#define TIBIA_5_PIN 6
#define FEMUR_5_THETA 90.0
#define TIBIA_5_THETA 95.0

// Back Right
#define FEMUR_6_PIN 13
#define TIBIA_6_PIN 12
#define FEMUR_6_THETA 83.0
#define TIBIA_6_THETA 87.0


void setup() {
    Serial.begin(115200);
    Serial.println("==== Testing Leg! ====");
    // Link tibia1 = Link(TIBIA_LENGTH, TIBIA_1_THETA, TIBIA_1_PIN);
    // Link femur1 = Link(FEMUR_LENGTH, FEMUR_1_THETA, FEMUR_1_PIN);
    // Leg  leg1 = Leg(tibia1, femur1);
    //
    // Link tibia2 = Link(TIBIA_LENGTH, TIBIA_2_THETA, TIBIA_2_PIN);
    // Link femur2 = Link(FEMUR_LENGTH, FEMUR_2_THETA, FEMUR_2_PIN);
    // Leg leg2 = Leg(tibia2, femur2);
    //
    // Link tibia3 = Link(TIBIA_LENGTH, TIBIA_3_THETA, TIBIA_3_PIN);
    // Link femur3 = Link(FEMUR_LENGTH, FEMUR_3_THETA, FEMUR_3_PIN);
    // Leg leg3 = Leg(tibia3, femur3);
    //
    // Link tibia4 = Link(TIBIA_LENGTH, TIBIA_4_THETA, TIBIA_4_PIN);
    // Link femur4 = Link(FEMUR_LENGTH, FEMUR_4_THETA, FEMUR_4_PIN);
    // Leg leg4 = Leg(tibia4, femur4);
    //
    // Link tibia5 = Link(TIBIA_LENGTH, TIBIA_5_THETA, TIBIA_5_PIN);
    // Link femur5 = Link(FEMUR_LENGTH, FEMUR_5_THETA, FEMUR_5_PIN);
    // Leg leg5 = Leg(tibia5, femur5);
    //
    // Link tibia6 = Link(TIBIA_LENGTH, TIBIA_6_THETA, TIBIA_6_PIN);
    // Link femur6 = Link(FEMUR_LENGTH, FEMUR_6_THETA, FEMUR_6_PIN);
    // Leg leg6 = Leg(tibia6, femur6);

    // Serial.println("==== Setting up Leg 1 (Front Left) ====");
    // leg1.setup();
    // delay(1000);
    // Serial.println("==== Setting up Leg 2 (Front Right) ====");
    // leg2.setup();
    // delay(1000);
    // Serial.println("==== Setting up Leg 3 (Center Left) ====");
    // leg3.setup();
    // delay(1000);
    // Serial.println("==== Setting up Leg 4 (Center Right) ====");
    // leg4.setup();
    // delay(1000);
    // Serial.println("==== Setting up Leg 5 (Back Left) ====");
    // leg5.setup();
    // delay(1000);
    // Serial.println("==== Setting up Leg 6 (Back Right) ====");
    // leg6.setup();
    CalibrationTool calibrationTool;
    calibrationTool.calibrateLegs(2, 13);
}

void loop() {
    // Keep alive
}