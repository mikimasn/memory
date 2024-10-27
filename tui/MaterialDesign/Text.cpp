#include "Text.h"

std::vector<char> &Memory::tui::Text::render(bool shouldNotifyParent) {
    for (int i = 0; i < (int)text.size(); i++) {
        framebuffer[i] = text[i];
        if (highlighted) framebuffer[i] |= HIGHLIGHT_TEXT;
    }
    return Element::render(shouldNotifyParent);
}
