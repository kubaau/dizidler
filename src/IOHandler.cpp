#include "IOHandler.hpp"

#include <SDL.h>

#include "Camera.hpp"
#include "Game.hpp"
#include "MidiPlayer.hpp"

using namespace std;

IOHandler::IOHandler(Game& game) : game(game), event(make_unique<SDL_Event>()) {}

IOHandler::~IOHandler() {}

void IOHandler::handleEvents()
{
    switch (game.stage)
    {
        case Stage::SPLASH: handleSplashEvents(); break;
        case Stage::PLAY: handlePlayEvents(); break;
        default:;
    }
}

void IOHandler::handleSplashEvents()
{
    while (SDL_PollEvent(event.get()))
        switch (event->type)
        {
            case SDL_KEYDOWN: game.play(); break;
            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT)
                    game.play();
                break;
            case SDL_QUIT: return game.stop();
        }
}

void IOHandler::handlePlayEvents()
{
    while (SDL_PollEvent(event.get()))
        switch (event->type)
        {
            case SDL_KEYDOWN: handlePlayKeyDown(); break;
            case SDL_QUIT: return game.stop();
        }
}

void IOHandler::handlePlayKeyDown()
{
    constexpr auto camera_pan_step = 0.01f;
    switch (event->key.keysym.sym)
    {
        case SDLK_UP: return game.camera->pan(0, camera_pan_step);
        case SDLK_DOWN: return game.camera->pan(0, -camera_pan_step);
        case SDLK_RIGHT: return game.midi_player->playNextTrack();
        case SDLK_ESCAPE: return game.stop();
    }
}
