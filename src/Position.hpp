#pragma once

#include <iostream>

template <typename T>
struct Position2D
{
    T x, y;

    friend auto& operator<<(std::ostream& os, const Position2D& pos) { return os << pos.x << "x" << pos.y; }
};

using Position2Df = Position2D<float>;
