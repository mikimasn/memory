#include "MemoryText.h"
#include <string>
#include <vector>
std::string toPrint = " /$$      /$$                                                      "
                      "| $$$    /$$$                                                      "
                      "| $$$$  /$$$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$   /$$$$$$  /$$   /$$"
                      "| $$ $$/$$ $$ /$$__  $$| $$_  $$_  $$ /$$__  $$ /$$__  $$| $$  | $$"
                      "| $$  $$$| $$| $$$$$$$$| $$ \\ $$ \\ $$| $$  \\ $$| $$  \\__/| $$  | $$"
                      "| $$\\  $ | $$| $$_____/| $$ | $$ | $$| $$  | $$| $$      | $$  | $$"
                      "| $$ \\/  | $$|  $$$$$$$| $$ | $$ | $$|  $$$$$$/| $$      |  $$$$$$$"
                      "|__/     |__/ \\_______/|__/ |__/ |__/ \\______/ |__/       \\____  $$"
                      "                                                          /$$  | $$"
                      "                                                         |  $$$$$$/"
                      "                                                          \\______/ ";
std::vector<char> &Memory::tui::MemoryText::render(bool shouldNotifyParent) {
    framebuffer.assign(currentsize.width * currentsize.height, ' ');
    for (int i = 0; i < toPrint.size(); i++) {
        framebuffer[i] = toPrint[i];
    }
    return framebuffer;
}
