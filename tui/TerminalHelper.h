#include <utility>
#include <vector>
#ifndef _WIN32
#include <termios.h>
#endif
namespace Memory::tui {
    struct TerminalInfo {
        int width;
        int height;
    };

    class TerminalHelper {
    private:
#ifndef _WIN32
        static termios oldTerminalSettings;
#endif
    public:
        static TerminalInfo getTerminalInfo();
        static void clearScreen();
        static void setupTerminal();
        static void pushToTerminal(const std::vector<char>& framebuffer);
        static void restoreTerminal();
    };
}

