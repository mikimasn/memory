#include "TerminalHelper.h"
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <iostream>
#include <csignal>

namespace Memory::tui {
    termios TerminalHelper::oldTerminalSettings;

    TerminalInfo TerminalHelper::getTerminalInfo() {
        struct winsize w;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
        if (w.ws_col < 50 || w.ws_row < 10) {
            std::cerr << "Terminal size is too small. Please resize the terminal to at least 20x10" << std::endl;
            std::raise(SIGABRT);
        }
        return {w.ws_col, w.ws_row};
    }

    void TerminalHelper::clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void TerminalHelper::setupTerminal() {
        std::cout << "\033[?25l\033[?1049h\033[?7h";
        struct termios raw;
        struct termios orig_termios;

        // Get current terminal attributes and save them in orig_termios
        tcgetattr(STDIN_FILENO, &orig_termios);
        TerminalHelper::oldTerminalSettings = orig_termios;
        raw = orig_termios;  // Make a copy of the original settings

        // Disable canonical mode, echoing
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN] = 1;                // Set minimum number of characters to read
        raw.c_cc[VTIME] = 0;               // No timeout for reading

        // Set the terminal to raw mode
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void TerminalHelper::restoreTerminal() {
        std::cout << "\033[?25h\033[?1049l\033[?7h";
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &TerminalHelper::oldTerminalSettings);
    }

    void TerminalHelper::pushToTerminal(const std::vector<char> &framebuffer) {
        std::string output;
        bool isHighliting = false;
        for (int i = 0; i < framebuffer.size(); i++) {
            char c = framebuffer[i];
            if (c & HIGHLIGHT_TEXT && !isHighliting) {
                output += "\033[7m";
                isHighliting = true;
            }
            if (!(c & HIGHLIGHT_TEXT) && isHighliting) {
                output += "\033[27m";
                isHighliting = false;
            }
            if (isHighliting) c &= ~HIGHLIGHT_TEXT;
            output += c;

        }
        std::cout << output;
        std::cout.flush();
    }

}
