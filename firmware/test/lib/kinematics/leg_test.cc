#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leg.h"
#include "i_servo.h"

using ::testing::NiceMock;

class MockServo : public IServo {
public:
    MOCK_METHOD(void, setup, (), (override));
    MOCK_METHOD(void, write, (int angle), (override));
};

class LegTest : public ::testing::Test {
protected:
    MockServo mock_coxa_servo;
    MockServo mock_femur_servo;

    Link coxa;
    Link femur;
    Leg leg;

    LegTest()
            : coxa(10.0f, 0.0f, mock_coxa_servo),
              femur(15.0f, 0.0f, mock_femur_servo),
              leg(coxa, femur) {}

    void SetUp() override {}
};

TEST_F(LegTest, SetupInitializesHardware) {
    EXPECT_CALL(mock_coxa_servo, write(0));
    EXPECT_CALL(mock_femur_servo, write(0));

    leg.setup();
}

TEST_F(LegTest, MoveWritesToBothServos) {
    GoalAngles goals = {45.0f, 90.0f};

    EXPECT_CALL(mock_coxa_servo, write(45));
    EXPECT_CALL(mock_femur_servo, write(90));

    leg.move(goals);
}
