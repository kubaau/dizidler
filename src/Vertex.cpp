#include "Vertex.hpp"

#include <GL/glew.h>

Vertex::Vertex(const Position2Df& p, const Color& c) : color(c), pos(p) {}

void Vertex::render() const
{
    glColor3f(color.r, color.g, color.b);
    glVertex2f(pos.x, pos.y);
}
