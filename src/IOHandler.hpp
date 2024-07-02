#pragma once

#include <memory>

class Game;

class IOHandler
{
public:
    IOHandler(Game&);
    ~IOHandler();

    void handleEvents();

private:
    void handleSplashEvents();
    void handlePlayEvents();

    void handlePlayKeyDown();

    Game& game;
    std::unique_ptr<union SDL_Event> event;
};
