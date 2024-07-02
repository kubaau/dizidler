#include <tools/ThreadSafeLogger.hpp>

#include "Game.hpp"
#include "Subsystems.hpp"

int main(int, char*[])
try
{
    initSubsystems();
    Game{}.run();
    unloadSubsystems();
    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    ERROR_LOG << ex.what();
    return EXIT_FAILURE;
}
