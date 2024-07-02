#include "Camera.hpp"

#include <GL/glew.h>

#include "Constants.hpp"

Camera::Camera() : pos{0, 0} {}

void Camera::pan(float x, float y)
{
    pos.x += x;
    pos.y += y;
}

void Camera::updatePerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    constexpr auto aspect = static_cast<float>(play_width) / play_height;
    gluOrtho2D(-1.0 * aspect + pos.x, 1.0 * aspect + pos.x, -1.0 + pos.y, 1.0 + pos.y);
}
