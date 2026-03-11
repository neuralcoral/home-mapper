#include <Arduino.h>

#include "leg.h"
#include "debug.h"

#define FEMUR_LENGTH 6.0
#define COXA_LENGTH 4.0

// Front Left
#define COXA_1_PIN 3
#define FEMUR_1_PIN 2
#define COXA_1_THETA 90.0
#define FEMUR_1_THETA 100.0

// Front Right
#define COXA_2_PIN 9
#define FEMUR_2_PIN 8
#define COXA_2_THETA 90.0
#define FEMUR_2_THETA 90.0

// Center Left
#define COXA_3_PIN 5
#define FEMUR_3_PIN 4
#define COXA_3_THETA 90.0
#define FEMUR_3_THETA 85.0

// Center Right
#define COXA_4_PIN 11
#define FEMUR_4_PIN 10
#define COXA_4_THETA 100.0
#define FEMUR_4_THETA 82.0

// Back Left
#define COXA_5_PIN 7
#define FEMUR_5_PIN 6
#define COXA_5_THETA 90.0
#define FEMUR_5_THETA 95.0

// Back Right
#define COXA_6_PIN 13
#define FEMUR_6_PIN 12
#define COXA_6_THETA 83.0
#define FEMUR_6_THETA 87.0

Link femur1(FEMUR_LENGTH, FEMUR_1_THETA, FEMUR_1_PIN);
Link coxa1(COXA_LENGTH, COXA_1_THETA, COXA_1_PIN);

Link femur2(FEMUR_LENGTH, FEMUR_2_THETA, FEMUR_2_PIN);
Link coxa2(COXA_LENGTH, COXA_2_THETA, COXA_2_PIN);

Link femur3(FEMUR_LENGTH, FEMUR_3_THETA, FEMUR_3_PIN);
Link coxa3(COXA_LENGTH, COXA_3_THETA, COXA_3_PIN);

Link femur4(FEMUR_LENGTH, FEMUR_4_THETA, FEMUR_4_PIN);
Link coxa4(COXA_LENGTH, COXA_4_THETA, COXA_4_PIN);

Link femur5(FEMUR_LENGTH, FEMUR_5_THETA, FEMUR_5_PIN);
Link coxa5(COXA_LENGTH, COXA_5_THETA, COXA_5_PIN);

Link femur6(FEMUR_LENGTH, FEMUR_6_THETA, FEMUR_6_PIN);
Link coxa6(COXA_LENGTH, COXA_6_THETA, COXA_6_PIN);

Leg leg1(coxa1, femur1);
Leg leg2(coxa2, femur2);
Leg leg3(coxa3, femur3);
Leg leg4(coxa4, femur4);
Leg leg5(coxa5, femur5);
Leg leg6(coxa6, femur6);

void setup() {
    Serial.begin(115200);
    delay(2000);
    LOG_INFO("==== Setting up Legs! ====");
    LOG_VAL("Setting up Leg", 1);
    leg1.setup();
    delay(1000);
    LOG_VAL("Setting up Leg", 2);
    leg2.setup();
    delay(1000);
    LOG_VAL("Setting up Leg", 3);
    leg3.setup();
    delay(1000);
    LOG_VAL("Setting up Leg", 4);
    leg4.setup();
    delay(1000);
    LOG_VAL("Setting up Leg", 5);
    leg5.setup();
    delay(1000);
    LOG_VAL("Setting up Leg", 6);
    leg6.setup();
    delay(1000);
    LOG_INFO("==== Set up Complete! ====");
}void loop() {
}
