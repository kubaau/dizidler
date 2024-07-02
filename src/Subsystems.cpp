#include "Subsystems.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_mixer.h>

namespace
{
    void initSDL() { SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); }

    void initGraphics()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        glewInit();
        constexpr auto vsync = true;
        SDL_GL_SetSwapInterval(vsync);
    }

    void initAudio() { Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 2048); }
}

void initSubsystems()
{
    initSDL();
    initGraphics();
    initAudio();
}

void unloadSubsystems()
{
    SDL_Quit();
}
