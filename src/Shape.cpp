#include "Shape.hpp"

#include <GL/glew.h>

Shape::Shape(Type ty, const Vertices& v, const Translation& tr) : translation(tr), type(ty), vertices(v) {}

void Shape::render() const
{
    glLoadIdentity();
    glTranslatef(translation.x, translation.y, 0);
    glBegin(type);
    for (const auto& vertex : vertices)
        vertex.render();
    glEnd();
}
