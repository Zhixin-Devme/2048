// Terminal.h Control the TUI Interface

#pragma once

#include <ios>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

class Terminal {
private:
    struct termios orig;
    struct termios raw;
public:
    static bool screen_resized;
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    Terminal();
    ~Terminal();
    void getWindowsSize(int &rows, int &cols);
    void clear();
    void moveCursor(int row, int col);
    void setColor(int color);
    char getInput();
    void hideCursor();
    void showCursor();
    void moveCursorBy(Direction d, int n);
};
