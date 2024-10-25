#include "Button.h"
#include "Positioner.h"

void Memory::tui::Button::setFocus(bool focused) {
    isFocused = focused;
    render(true);
}

Memory::tui::InputActionResult Memory::tui::Button::handleInput(Memory::tui::InputSignal &c) {
    if (c.group == InputGroup::ENTER) {
        callback();
        return InputActionResult::VOID;
    }
    return InputActionResult::NOT_HANDLED;
}

std::vector<char> &Memory::tui::Button::render(bool shouldNotifyParent) {
    framebuffer.assign(currentsize.width * currentsize.height, ' ');
    this->textElement.setHighlighted(isFocused, false);
    this->getChild(0).element = &this->textElement;
    return Element::render(shouldNotifyParent);
}

void Memory::tui::Button::init() {
    Positioner::center(*this, this->getChild(0));
};

