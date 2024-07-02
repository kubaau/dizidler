#include "Window.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Constants.hpp"

using namespace std;

constexpr auto menu_width = 640;
constexpr auto menu_height = 480;

Window::Window()
    : window(SDL_CreateWindow(title.c_str(), 400, 200, menu_width, menu_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN))
{
    const auto window_surface = SDL_GetWindowSurface(window);
    const auto surface_temp = IMG_Load((asset_folder + "GFX/PICS/SETUP998.LBM").c_str());
    surface = SDL_ConvertSurface(surface_temp, window_surface->format, 0);
    SDL_FreeSurface(surface_temp);
    SDL_BlitScaled(surface, nullptr, window_surface, nullptr);
    SDL_UpdateWindowSurface(window);

    SDL_GL_CreateContext(window);
}

Window::~Window()
{
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
}

void Window::setTitle(string title)
{
    SDL_SetWindowTitle(window, title.c_str());
}

void Window::resize(int width, int height)
{
    SDL_SetWindowSize(window, width, height);
    glViewport(0, 0, width, height);
}

void Window::swapBuffers()
{
    SDL_GL_SwapWindow(window);
}
