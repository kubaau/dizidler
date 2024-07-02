#pragma once

#include "Color.hpp"
#include "Position.hpp"

class Vertex
{
public:
    Vertex(const Position2Df&, const Color&);

    void render() const;

private:
    Color color;
    Position2Df pos;
};
