#include "FrameCounter.hpp"

#include "Constants.hpp"
#include "Window.hpp"

using namespace std;

void FrameCounter::tick()
{
    ++count;
}

void FrameCounter::updateDisplay(Window& window)
{
    window.setTitle(title + " " + to_string(count) + " FPS");
    count = 0;
}
