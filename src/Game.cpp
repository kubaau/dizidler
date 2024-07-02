#include "Game.hpp"

#include <GL/glew.h>

#include <tools/TaskScheduler.hpp>

#include "Camera.hpp"
#include "Constants.hpp"
#include "FrameCounter.hpp"
#include "IOHandler.hpp"
#include "MidiPlayer.hpp"
#include "Window.hpp"
#include "World.hpp"

using namespace std;

Game::Game()
    : ts(make_unique<TaskScheduler>()),
      window(make_unique<Window>()),
      world(make_unique<World>()),
      camera(make_unique<Camera>()),
      frame_counter(make_unique<FrameCounter>()),
      midi_player(make_unique<MidiPlayer>()),
      io_handler(make_unique<IOHandler>(*this))
{
}

Game::~Game() {}

void Game::run()
{
    ts->schedule([this] { frame_counter->tick(); }, no_delay, unlimited_repetitions);
    ts->schedule([this] { frame_counter->updateDisplay(*window); }, 1s, unlimited_repetitions);

    while (stage != Stage::QUIT)
    {
        ts->launch();

        io_handler->handleEvents();

        if (stage == Stage::PLAY)
        {
            update();
            render();
        }
    }
}

void Game::play()
{
    stage = Stage::PLAY;
    window->resize(play_width, play_height);
}

void Game::stop()
{
    stage = Stage::QUIT;
}

void Game::update()
{
    world->update();
    camera->updatePerspective();
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    world->render();
    window->swapBuffers();
}
