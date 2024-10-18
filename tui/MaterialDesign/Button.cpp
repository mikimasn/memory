#include "Button.h"
void Memory::tui::Button::setFocus(bool focused) {
        if(focused) text+=" *";
        else {
            text.pop_back();
            text.pop_back();
        }
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
        return Element::render(shouldNotifyParent);
};

