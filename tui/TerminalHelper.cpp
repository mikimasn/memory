#include "TerminalHelper.h"

#ifdef _WIN32
#include <windows.h>
#else

#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <iostream>
#include <armadillo>

#endif

namespace Memory::tui {
     termios TerminalHelper::oldTerminalSettings;
     TerminalInfo TerminalHelper::getTerminalInfo() {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return {csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
#else
        struct winsize w;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
        return {w.ws_col, w.ws_row};
#endif
    }

    void TerminalHelper::clearScreen() {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        TerminalInfo terminalInfo = getTerminalInfo();
        DWORD consoleSize = terminalInfo.width * terminalInfo.height;
        COORD coord = {0, 0};
        DWORD written;
        FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coord, &written);
        SetConsoleCursorPosition(hConsole, coord);
#else
        std::cout << "\033[2J\033[1;1H";
#endif
    }

    void TerminalHelper::setupTerminal() {
#ifdef _WIN32
        // Not implemented
#else
        std::cout<<"\033[?25l";
        struct termios raw;
        struct termios orig_termios;

        // Get current terminal attributes and save them in orig_termios
        tcgetattr(STDIN_FILENO, &orig_termios);
        TerminalHelper::oldTerminalSettings=orig_termios;
        raw = orig_termios;  // Make a copy of the original settings

        // Disable canonical mode, echoing
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN] = 1;                // Set minimum number of characters to read
        raw.c_cc[VTIME] = 0;               // No timeout for reading

        // Set the terminal to raw mode
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
#endif
    }
    void TerminalHelper::restoreTerminal() {
#ifdef _WIN32
        // Not implemented
#else
        std::cout<<"\033[?25h";
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &TerminalHelper::oldTerminalSettings);
#endif
     }

    void TerminalHelper::pushToTerminal(const std::vector<char> &framebuffer) {
        std::string output;
        bool isHighliting=false;
        for (int i=0;i<framebuffer.size();i++){
            char c = framebuffer[i];
            if(c&HIGHLIGHT_TEXT&&!isHighliting){
                output += "\033[7m";
                isHighliting=true;
            }
            if(!(c&HIGHLIGHT_TEXT)&&isHighliting){
                output += "\033[27m";
                isHighliting=false;
            }
            if(isHighliting) c &= ~HIGHLIGHT_TEXT;
            output += c;

        }
        std::cout << output;
        std::cout.flush();
    }

}
