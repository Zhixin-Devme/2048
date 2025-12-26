#include "../include/Controller.h"

void Controller::handleInput(char input) {
    switch (input) {
        case 'w':
            game.slide(Game::DIRC::NORTH);
            break;
        case 's':
            game.slide(Game::DIRC::SOUTH);
            break;
        case 'a':
            game.slide(Game::DIRC::WEST);
            break;
        case 'd':
            game.slide(Game::DIRC::EAST);
            break;
        default:
            return;
    }

    if (game.changed) {
        game.spawn();
        game.changed = false;
    }
}
