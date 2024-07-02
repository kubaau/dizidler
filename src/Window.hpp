#pragma once

#include <string>

class Window
{
public:
    Window();
    ~Window();

    void setTitle(std::string);
    void resize(int width, int height);
    void swapBuffers();

private:
    struct SDL_Window* window;
    struct SDL_Surface* surface;
    struct SDL_Renderer* renderer;
};
