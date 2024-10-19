#include "Button.h"
#include "../TerminalHelper.h"
void Memory::tui::Button::setFocus(bool focused) {
    isFocused = focused;
    render(true);
}

Memory::tui::InputActionResult Memory::tui::Button::handleInput(Memory::tui::InputSignal &c) {
        if(c.group == InputGroup::ENTER){
            callback();
            return InputActionResult::VOID;
        }
        return Element::handleInput(c);
}

std::vector<char> &Memory::tui::Button::render(bool shouldNotifyParent) {
        framebuffer.assign(currentsize.width * currentsize.height, ' ');
        for(int i=0; i<text.size(); i++){
            framebuffer[i]=text[i];
        }
        if(isFocused) for(char& i : framebuffer) i |= HIGHLIGHT_TEXT;
        return Element::render(shouldNotifyParent);
};

