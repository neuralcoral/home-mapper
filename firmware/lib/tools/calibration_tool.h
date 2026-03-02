#ifndef HEXAPOD_DIAGNOSTICS_TOOL_H
#define HEXAPOD_DIAGNOSTICS_TOOL_H


class CalibrationTool
{
    public:
    CalibrationTool();
    void calibrateLegs(const int& startPin, const int& endPin);

};


#endif //HEXAPOD_DIAGNOSTICS_TOOL_H