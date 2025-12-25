#include "../include/Terminal.h"
#include <cstdio>
#include <unistd.h>

int main () {
    Terminal terminal;
    terminal.clear();
    terminal.moveCursor(10, 200);
    printf("Wow!");
    fflush(stdout);
    sleep(2);
    terminal.moveCursorBy(Terminal::Direction::DOWN, 10);
    fflush(stdout);
    sleep(2);
    terminal.moveCursor(300, 50);
    fflush(stdout);
    sleep(1);
    printf("Hello....");
    fflush(stdout);
    sleep(4);
    terminal.clear();
    return 0;
}
