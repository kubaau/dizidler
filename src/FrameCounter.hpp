#pragma once

#include <tools/Typedefs.hpp>

class Window;

class FrameCounter
{
public:
    void tick();
    void updateDisplay(Window&);

private:
    Count count = 0;
};
