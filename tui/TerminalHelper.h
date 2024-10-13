#include <utility>
#include <vector>

namespace Memory::tui {
    struct TerminalInfo {
        int width;
        int height;
    };

    class TerminalHelper {
    public:
        static TerminalInfo getTerminalInfo();
        static void clearScreen();
        static void setupTerminal();
        static void pushToTerminal(const std::vector<char>& framebuffer);
    };
}

