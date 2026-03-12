#ifndef HOME_MAPPER_ISERVO_H
#define HOME_MAPPER_ISERVO_H

class IServo {
public:
    virtual ~IServo() = default;
    virtual void setup() = 0;
    virtual void write(int angle) = 0;
};

#endif //HOME_MAPPER_ISERVO_H
