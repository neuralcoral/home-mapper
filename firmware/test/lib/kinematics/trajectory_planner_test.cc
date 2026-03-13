#include "mock_servo.h"
#include "gtest/gtest.h"
#include "trajectory_planner.h"
#include "leg.h"

using ::testing::_;
using ::testing::AtLeast;

class TrajectoryPlannerTest : public ::testing::Test {
protected:
    MockServo mock_coxa_servo;
    MockServo mock_femur_servo;

    Link coxa;
    Link femur;
    Leg leg;
    TrajectoryPlanner planner;

    LegAngleLimits limits;

    TrajectoryPlannerTest()
            : coxa(10.0f, 0.0f, mock_coxa_servo),
              femur(15.0f, 0.0f, mock_femur_servo),
              leg(coxa, femur) {

        // Define some standard limits for testing
        limits.coxa_link_limit = {0.0f, 180.0f};
        limits.femur_link_limit = {0.0f, 90.0f};
    }
};

// Test 1: Verify Swing Phase Calculations (Phase < 0.5)
TEST_F(TrajectoryPlannerTest, PlanSwingPhaseCalculatesCorrectAngles) {
    float phase = 0.25f; // Middle of swing phase

    // Expected calculations based on your math:
    // coxa: 180 * sin(PI * 0.25) = 180 * 0.707 = ~127
    // femur: 90 * (2 * 0.25)^2 = 90 * 0.25 = 22.5 -> 22

    EXPECT_CALL(mock_coxa_servo, write(127));
    EXPECT_CALL(mock_femur_servo, write(22));

    planner.plan(leg, limits, phase);
}

// Test 2: Verify Stance Phase Initial Transition (Phase >= 0.5)
TEST_F(TrajectoryPlannerTest, PlanStancePhaseCalculatesCorrectAngles) {
    float phase = 0.6f;

    // coxa: 180 * sin(PI * 0.6) = 180 * 0.951 = ~171
    // femur: phase is 0.6 (< 0.9), so returns limits.lower_bound (0)

    EXPECT_CALL(mock_coxa_servo, write(171));
    EXPECT_CALL(mock_femur_servo, write(0));

    planner.plan(leg, limits, phase);
}

// Test 3: Verify Stance Phase Near Completion (Phase > 0.9)
TEST_F(TrajectoryPlannerTest, PlanStancePhaseCalculatesRecoveryAtEnd) {
    float phase = 0.95f;

    // femur recovery logic: 90 * cos(HALF_PI * (0.95 - 0.9) / 0.1)
    // = 90 * cos(HALF_PI * 0.5) = 90 * cos(PI/4) = 90 * 0.707 = ~63

    EXPECT_CALL(mock_femur_servo, write(63));
    EXPECT_CALL(mock_coxa_servo, write(_)); // Ignore coxa for this specific check

    planner.plan(leg, limits, phase);
}