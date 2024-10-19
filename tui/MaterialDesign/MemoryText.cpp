#include "MemoryText.h"
#include <string>
#include <vector>
std::string toPrint = " __  __                                 "
                      "|  \\/  | ___ _ __ ___   ___  _ __ _   _ "
                      "| |\\/| |/ _ \\ '_ ` _ \\ / _ \\| '__| | | |"
                      "| |  | |  __/ | | | | | (_) | |  | |_| |"
                      "|_|  |_|\\___|_| |_| |_|\\___/|_|   \\__, |"
                      "                                  |___/ ";
std::vector<char> &Memory::tui::MemoryText::render(bool shouldNotifyParent) {
    framebuffer.assign(currentsize.width * currentsize.height, ' ');
    for (int i = 0; i < toPrint.size(); i++) {
        framebuffer[i] = toPrint[i];
    }
    return framebuffer;
}
