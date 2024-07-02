#pragma once

#include "Position.hpp"

class Camera
{
public:
    Camera();

    void pan(float x, float y);
    void updatePerspective();

private:
    Position2Df pos;
};
