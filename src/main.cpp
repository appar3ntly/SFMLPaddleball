#include <iostream>
#include "config.h"
#include "SFMLPaddleball/game.hpp"

int main()
{
    // Print version number to terminal.
    std::cout << "SFML Paddleball Version: " << SFMLPaddleball_VERSION_MAJOR << "."
              << SFMLPaddleball_VERSION_MINOR << std::endl;
    // Seed random number generator for game.
    srand(time(0));

    // Start game and turn over control.
    Game game;
    game.start();

    return 0;
}