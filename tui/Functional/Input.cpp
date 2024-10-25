#include <csignal>
#include "Input.h"
#include "Interupts.h"

namespace Memory::tui {

    InputSignal InputHandler::parseInput(char *c) {
        switch (c[0]) {
            case '\033':
                switch (c[2]) {
                    case 'A':
                        return {ARROW_KEYS, 0};
                    case 'B':
                        return {ARROW_KEYS, 1};
                    case 'C':
                        return {ARROW_KEYS, 2};
                    case 'D':
                        return {ARROW_KEYS, 3};
                    default:
                        return {UNKNOWN, c[0]};
                }
            case '\n':
                return {ENTER, 0};
            case '\177':
                return {BACKSPACE, 0};
            case '0' ... '9':
                return {NUMBERS, c[0]};
            case 'A' ... 'Z':
            case 'a' ... 'z':
            case ' ':
            case '/':
            case '\\':
            case '.':
                return {TEXT, c[0]};
            default:
                return {UNKNOWN, c[0]};
        }
    }

    InputActionResult InputHandler::convertArrowKeys(InputSignal signal) {
        if (signal.group != ARROW_KEYS) {
            return NOT_HANDLED;
        }
        switch (signal.c) {
            case 0:
                return MOVE_UP;
            case 1:
                return MOVE_DOWN;
            case 2:
                return MOVE_RIGHT;
            case 3:
                return MOVE_LEFT;
            default:
                return NOT_HANDLED;
        }
    }

    InputSignal InputHandler::blockForInput() {
        char c[3];
        read(STDIN_FILENO, c, 3);
        //detect when the input stream is closed
        if (c[0] == 0) {
            Interupts::handleTermination(0);
        }
        return parseInput(c);
    }
}