#pragma once

#include "Terminal.h"
#include "Game.h"
#include <string>
#include <cstdio>
#include <unistd.h>

class Renderer {
private:
    const char* TOP_LEFT = "┌";
    const char* TOP_RIGHT = "┐";
    const char* BOTTOM_LEFT = "└";
    const char* BOTTOM_RIGHT = "┘";
    const char* HORIZONTAL = "─";
    const char* VERTICAL = "│";
    int win_rows = 0;
    int win_cols = 0;
    int padding = 0;
    int tile_w = 0;
    int tile_h = 0;
    int orig_x = 0;
    int orig_y = 0;
    Terminal terminal;
    struct Rec {
        int x, y, w, h;
    };
    Rec mainFrame;
public:
    Renderer();
    ~Renderer();
    void render(const std::vector<std::vector<int>> &board, const int score);
    void updateLayout();
    void helloTest();
    void drawBox(Rec r);
    void printCenter(Rec r, std::string text);
    void printAt(int x, int y, std::string text);
    void drawTile(int pos_x, int pos_y, int num);
    void setBColor(int num);
    void unsetBColor();
    void fillBox(Rec r);
    int getStartPos(int containerStart, int containerLen, int contentLen);
};

