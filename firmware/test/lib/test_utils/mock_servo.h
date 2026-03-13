#include "firmware/lib/kinematics/i_servo.h"
#include "gmock/gmock.h"


class MockServo : public IServo {
public:
    MOCK_METHOD(void, setup, (), (override));
    MOCK_METHOD(void, write, (int angle), (override));
};
