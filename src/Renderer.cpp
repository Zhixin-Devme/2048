#include "../include/Renderer.h"
#include <cstdio>
#include <string>
#include <math.h>

Renderer::Renderer() {
    terminal.getWindowsSize(win_rows, win_cols);
    terminal.hideCursor();
    padding = 1;
}

Renderer::~Renderer() {
    terminal.showCursor();
}

void Renderer::render(const std::vector<std::vector<int>> &board, const int score) {
    updateLayout();
    drawBox(mainFrame);
    printAt(win_cols / 2, win_rows / 10, "2048");
    printAt(win_cols / 10, win_rows / 2, "SCORE: " + std::to_string(score));
    Rec base = {orig_x - 1, orig_y - 1, 4 * (tile_w + padding) + 1, 4 * (tile_h + padding) + 1};
    drawBox(base);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            drawTile(col, row, board[row][col]);
        }
    }
    fflush(stdout);
}

void Renderer::updateLayout() {
    terminal.getWindowsSize(win_rows, win_cols);
    int main_x = win_cols / 20;
    int main_y = win_rows / 20;
    mainFrame = {main_x, main_y, win_cols - 2 * main_x, win_rows - 2 * main_y};
    tile_w = std::min(mainFrame.h, mainFrame.w) / 3;
    tile_h = tile_w / 2;
    int totalW = 4 * tile_w + 3 * padding;
    int totalH = 4 * tile_h + 3 * padding;
    orig_x = getStartPos(mainFrame.x, mainFrame.w, totalW);
    orig_y = getStartPos(mainFrame.y, mainFrame.h, totalH);
    terminal.clear();
}

void Renderer::drawBox(Rec r) {
    terminal.moveCursor(r.y, r.x);
    printf(TOP_LEFT);
    for (int i = 0; i < r.w - 2; i++) {
        printf(HORIZONTAL);
    }
    printf(TOP_RIGHT);
    for (int i = 1; i < r.h - 1; i++) {
        terminal.moveCursor(r.y + i, r.x);
        printf(VERTICAL);
        terminal.moveCursor(r.y + i, r.x + r.w - 1);
        printf(VERTICAL);
    }
    terminal.moveCursor(r.y + r.h - 1, r.x);
    printf(BOTTOM_LEFT);
    for (int i = 0; i < r.w - 2; i++) {
        printf(HORIZONTAL);
    }
    printf(BOTTOM_RIGHT);
}

void Renderer::printCenter(Rec r, std::string text) {
    terminal.moveCursor(r.y + r.h / 2, r.x + r.w / 2 - text.length() / 2);
    printf("%s", text.c_str());
}

void Renderer::printAt(int x, int y, std::string text) {
    terminal.moveCursor(y, x - text.length() / 2);
    printf("%s", text.c_str());
}

void Renderer::drawTile(int pos_x, int pos_y, int num) {
    Rec tile = {orig_x + pos_x * (tile_w + padding), orig_y + pos_y * (tile_h + padding), tile_w, tile_h};
    setBColor(num);
    fillBox(tile);
    printCenter(tile, std::to_string(num));
    unsetBColor();
}

void Renderer::setBColor(int num) {
    switch(num) {
        case 0:
            printf("\033[48;5;237m");
            break;
        case 2:
            printf("\033[48;5;214m\033[38;5;0m");
            break;
        case 4:
            printf("\033[48;5;208m\033[38;5;0m");
            break;
        case 8:
            printf("\033[48;5;202m\033[38;5;15m");
            break;
        case 16:
            printf("\033[48;5;196m\033[38;5;15m");
            break;
        case 32:
            printf("\033[48;5;160m\033[38;5;15m");
            break;
        case 64:
            printf("\033[48;5;124m\033[38;5;15m");
            break;
        case 128:
            printf("\033[48;5;127m\033[38;5;15m");
            break;
        case 256:
            printf("\033[48;5;129m\033[38;5;15m");
            break;
        case 512:
            printf("\033[48;5;93m\033[38;5;15m");
            break;
        case 1024:
            printf("\033[48;5;57m\033[38;5;15m");
            break;
        case 2048:
            printf("\033[48;5;21m\033[38;5;15m");
            break;
        default:
            printf("\033[48;5;0m\033[38;5;15m");
            break;
    }
}

void Renderer::unsetBColor() {
    printf("\033[0m");
}

void Renderer::fillBox(Rec r) {
    for (int j = 1; j < r.h - 1; j++) {
        terminal.moveCursor(r.y + j, r.x + 1);
        for (int i = 0; i < r.w - 2; i ++) {
            printf(" ");
        }
    }
}

int Renderer::getStartPos(int containerStart, int containerLen, int contentLen) {
    return containerStart + (containerLen - contentLen) / 2;
}
