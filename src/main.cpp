#include "../include/Renderer.h"
#include "../include/Controller.h"
#include <csignal>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <cstring>

void handleSigwinch(int sig) {
    Terminal::screen_resized = true;
}

int main () {
    Renderer viewer;
    Game game;
    Controller controller(game);
    signal(SIGWINCH, handleSigwinch);

    char ch = 0;
    while (ch != 'q') {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 20000;

        int reval = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

        if (reval == -1) {
            if (errno == EINTR) {
                if (Terminal::screen_resized) {
                    viewer.updateLayout();
                    viewer.render(game.board, game.score);
                    Terminal::screen_resized = false;
                }
                continue;
            } else {
                perror("select error");
                break;
            }
        } else if (reval == 0) {
            viewer.render(game.board, game.score);
        } else {
            if (FD_ISSET(STDIN_FILENO, &read_fds)) {
                read(STDIN_FILENO, &ch, 1);
                controller.handleInput(ch);
                viewer.render(game.board, game.score);
            }
        }
    }


    return 0;
}
