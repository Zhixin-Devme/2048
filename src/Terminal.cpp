#include "../include/Terminal.h"
#include <cstdio>

bool Terminal::screen_resized = false;

Terminal::Terminal() {
    tcgetattr(STDIN_FILENO, &raw);
    orig = raw;
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);  // 关闭回显、行缓冲、扩展、信号
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);  // 关闭一些输入处理
    raw.c_cflag |= (CS8);      // 8位字符
    raw.c_oflag &= ~(OPOST);   // 关闭输出处理（如\n→\r\n）
    raw.c_cc[VMIN] = 1;   // 或 1，取决于你想阻塞还是非阻塞
    raw.c_cc[VTIME] = 0;  // 单位 0.1s，常设为 1 表示 100ms 超时
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\033[?1049h");
    fflush(stdout);
}

Terminal::~Terminal() {
    printf("\033[?1049l");
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
    fflush(stdout);
}

void Terminal::getWindowsSize(int &rows, int &cols) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
}

void Terminal::clear() {
    printf("\033[2J");
}

void Terminal::moveCursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void Terminal::hideCursor() {
    printf("\033[?25l");
}

void Terminal::showCursor() {
    printf("\033[?25h");
}

void Terminal::moveCursorBy(Direction d, int n) {
    if (d == Direction::UP) {
        printf("\033[%dA", n);
    } else if (d == Direction::DOWN) {
        printf("\033[%dB", n);
    } else if (d == Direction::RIGHT) {
        printf("\033[%dC", n);
    } else {
        printf("\033[%dD", n);
    }
}


