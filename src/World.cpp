#include "World.hpp"

#include <GL/glew.h>

#include "Colors.hpp"
#include "Loading.hpp"

World::World()
{
    createDefault();
    load();
}

void World::update() {}

void World::render() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for (const auto& shape : shapes)
        shape.render();
    glPopMatrix();
}

void World::createDefault()
{
    Vertices v;
    v.emplace_back(Position2Df{-0.1f, -0.2f}, yellow);
    v.emplace_back(Position2Df{0.1f, -0.2f}, yellow);
    v.emplace_back(Position2Df{0.2f, 0.0f}, yellow);
    v.emplace_back(Position2Df{0.1f, 0.2f}, yellow);
    v.emplace_back(Position2Df{-0.1f, 0.2f}, yellow);
    v.emplace_back(Position2Df{-0.2f, 0.0f}, yellow);
    shapes.emplace_back(GL_POLYGON, v, Translation{0.0f, 0.0f});

    v.clear();
    v.emplace_back(Position2Df{-0.1f, -0.2f}, red);
    v.emplace_back(Position2Df{0.1f, -0.2f}, red);
    v.emplace_back(Position2Df{0.2f, 0.0f}, red);
    v.emplace_back(Position2Df{0.1f, 0.2f}, red);
    v.emplace_back(Position2Df{-0.1f, 0.2f}, red);
    v.emplace_back(Position2Df{-0.2f, 0.0f}, red);
    shapes.emplace_back(GL_POLYGON, v, Translation{0.0f, 0.4f});

    v.clear();
    v.emplace_back(Position2Df{-0.1f, -0.2f}, blue);
    v.emplace_back(Position2Df{0.1f, -0.2f}, blue);
    v.emplace_back(Position2Df{0.2f, 0.0f}, blue);
    v.emplace_back(Position2Df{0.1f, 0.2f}, blue);
    v.emplace_back(Position2Df{-0.1f, 0.2f}, blue);
    v.emplace_back(Position2Df{-0.2f, 0.0f}, blue);
    shapes.emplace_back(GL_POLYGON, v, Translation{0.0f, -0.4f});
}
