#include "InputBox.h"
#include <iostream>
Memory::tui::InputActionResult Memory::tui::InputBox::handleInput(Memory::tui::InputSignal &c) {

    if(c.group==InputGroup::TEXT||c.group==InputGroup::NUMBERS){
        if(pointer==textElement.text.size()) return InputActionResult::VOID;
        textElement.text[pointer]&=~HIGHLIGHT_TEXT;
        textElement.text[pointer++]=c.c;
        if(pointer<textElement.text.size())textElement.text[pointer]|=HIGHLIGHT_TEXT;
        textElement.render(true);
        return InputActionResult::VOID;
    }
    if(c.group==InputGroup::BACKSPACE){
        if(pointer==0) return InputActionResult::VOID;
        textElement.text[pointer]&=~HIGHLIGHT_TEXT;
        textElement.text[--pointer]='_';
        textElement.text[pointer]|=HIGHLIGHT_TEXT;
        textElement.render(true);
        return InputActionResult::VOID;
    }
    return Element::handleInput(c);
}

void Memory::tui::InputBox::setFocus(bool focused) {
    if(focused) textElement.text[pointer]|=HIGHLIGHT_TEXT;
    else textElement.text[pointer]&=~HIGHLIGHT_TEXT;
    textElement.render(true);
}

void Memory::tui::InputBox::init(const ElementSize &size) {
    framebuffer.resize(size.width * size.height);
    for(int i=0;i<size.width;i++) textElement.text.push_back('_');
}
