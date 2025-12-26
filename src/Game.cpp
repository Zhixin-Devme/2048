#include "../include/Game.h"


Game::Game() {
    score = 0;
    pov = DIRC::SOUTH;
    isGameOver = false;
    changed = false;
    board = std::vector<std::vector<int>>(4, std::vector<int>(4,0));
    setPOV(DIRC::SOUTH);
    srand(static_cast<unsigned int>(time(NULL)));
    spawn();
    spawn();
}

Game::~Game() {
}

void Game::setPOV(DIRC d) {
    if (d == DIRC::SOUTH) {
        x0 = y0 = 0;
        dx = 0;
        dy = 1;
    } else if (d == DIRC::NORTH) {
        x0 = 3;
        y0 = 3;
        dx = 0;
        dy = -1;
    } else if (d == DIRC::WEST) {
        x0 = 3;
        y0 = 0;
        dx = -1;
        dy = 0;
    } else if (d == DIRC::EAST) {
        x0 = 0;
        y0 = 3;
        dx = 1;
        dy = 0;
    }
}

int Game::getTile(Tile t) {
    int real_x = x0 + (t.x * dy) + (t.y * dx);
    int real_y = y0 + (t.x * -dx) + (t.y * dy);
    return board[real_y][real_x];
}

void Game::slide(DIRC d) {
    setPOV(d);
    for (int i = 0; i < 4; i++) {
        int count = 3;
        Tile prev = {-1, -1};
        for (int j = 3; j >= 0; j--) {
            Tile ptr = {i, j};
            if (getTile(ptr) != 0) {
                if (prev.x != -1) {
                    if (getTile(prev) == getTile(ptr)) {
                        move(ptr, prev);
                        if (count != prev.x) changed = true;
                        move(prev, {i, count});
                        count--;
                        prev = {-1, -1};
                    } else {
                        move(prev, {i, count});
                        if (count != prev.x) changed = true;
                        count--;
                        prev = ptr;
                        changed = true;
                    }
                } else {
                    prev = ptr;
                }
            }
        }
        if (prev.x != -1) {
            if (count != prev.x) changed = true;
            move(prev, {i, count});
        }
    }
}

void Game::setTile(Tile t, int val) {
    int real_x = x0 + (t.x * dy) + (t.y * dx);
    int real_y = y0 + (t.x * -dx) + (t.y * dy);
    board[real_y][real_x] =  val;
}


bool Game::move(Tile from, Tile to) {
    if (from.x == to.x && from.y == to.y) {
        return false;
    }
    if (getTile(to) == 0) {
        setTile(to, getTile(from));
        setTile(from, 0);
        return true;
    } else {
        if (getTile(to) == getTile(from)) {
            merge(from, to);
            return true;
        } else {
            return false;
        }
    }
}

void Game::merge(Tile from, Tile to) {
    int points = getTile(from) + getTile(to);
    score += points;
    setTile(to, points);
    setTile(from, 0);
}

bool Game::checkGameOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            Tile ptr = {i, j};
            Tile ptr2 = {i, j+1};
            Tile ptr3 = {j, i};
            Tile ptr4 = {j+1, i};
            if (getTile(ptr) == 0 || getTile(ptr3) == 0) {
                return false;
            } else if (getTile(ptr) == getTile(ptr2) || getTile(ptr3) == getTile(ptr4)) {
                return false;
            }
        }
    }
    return true;
}

void Game::spawn() {
    std::vector<Tile> empities;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (board[row][col] == 0) {
                empities.push_back({col, row});
            }
        }
    }
    
    if (empities.empty()) { 
        isGameOver = checkGameOver();
        return; 
    }
    Tile target = empities[rand() % empities.size()];
    board[target.y][target.x] = (rand() % 10 == 0) ? 4 : 2;
}


