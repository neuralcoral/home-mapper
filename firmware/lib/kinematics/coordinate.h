#ifndef HEXAPOD_COORDINATE_H
#define HEXAPOD_COORDINATE_H

struct CartesianCoordinate
{
    float x, y, z;
};

struct CylindricalCoordinate
{
    float r, theta, z;
};

#endif //HEXAPOD_COORDINATE_H