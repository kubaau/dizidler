#pragma once

#include "Shape.hpp"

class World
{
public:
    World();

    void update();
    void render() const;

private:
    void createDefault();

    std::vector<Shape> shapes;
};
