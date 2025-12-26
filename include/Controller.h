#pragma once
#include "Game.h"

class Controller {
private:
    Game& game;

public:
    Controller(Game& g) : game(g) {}

    void handleInput(char input);
};
