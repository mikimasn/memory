#pragma once

#include <utility>
#include <vector>
#include <termios.h>

#define HIGHLIGHT_TEXT 128
namespace Memory::tui {
    struct TerminalInfo {
        int width;
        int height;
    };

    class TerminalHelper {
    private:
        static termios oldTerminalSettings;
    public:
        static TerminalInfo getTerminalInfo();

        static void clearScreen();

        static void setupTerminal();

        static void pushToTerminal(const std::vector<char> &framebuffer);

        static void restoreTerminal();
    };
}

