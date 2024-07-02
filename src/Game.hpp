#pragma once

#include <memory>

#include "Stage.hpp"

class Game
{
    friend class IOHandler;

public:
    Game();
    ~Game();

    void run();
    void play();
    void stop();

private:
    void update();
    void render();

    Stage stage = Stage::SPLASH;
    std::unique_ptr<class TaskScheduler> ts;
    std::unique_ptr<class Window> window;
    std::unique_ptr<class World> world;
    std::unique_ptr<class Camera> camera;
    std::unique_ptr<class FrameCounter> frame_counter;
    std::unique_ptr<class MidiPlayer> midi_player;
    std::unique_ptr<class IOHandler> io_handler;
};
