#pragma once
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
class Game {
private:
    int x0;
    int y0;
    int dx;
    int dy;
public:
    struct Tile {
        int x, y;
    };
    enum class DIRC {
        NORTH,
        SOUTH,
        WEST,
        EAST
    };
    int score;
    bool isGameOver;
    bool changed;
    std::vector<std::vector<int>> board;
    DIRC pov;

    Game();
    ~Game();
    void setPOV(DIRC d);
    void slide(DIRC d);
    int getTile(Tile t);
    void setTile(Tile t, int val);
    bool move(Tile from, Tile to);
    void merge(Tile from, Tile to);
    bool checkGameOver();
    void spawn();
};
       
