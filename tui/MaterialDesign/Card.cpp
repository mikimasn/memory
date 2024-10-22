#include "Card.h"
#include <string>
std::string rewers="--. "
                   " .. "
                   " --."
                   ".- ";
Memory::tui::InputActionResult Memory::tui::Card::handleInput(Memory::tui::InputSignal &signal) {
    if(signal.group==InputGroup::ENTER){
        isFlipped = !isFlipped;
        this->render(true);
        return InputActionResult::VOID;
    }
    return Element::handleInput(signal);
}

std::vector<char> &Memory::tui::Card::render(bool shouldNotifyParent) {
    Element::render(shouldNotifyParent);
    for(int i=1; i<5; i++){
        for(int j=1; j<5; j++){
            if(isFlipped) framebuffer[i*currentsize.width+j] = rewers[(i-1)*4+j-1];
            else framebuffer[i*currentsize.width+j] = front&(1<<((i-1)*4+j-1))?'@':'$';
        }
    }
    if(isFocused) for(char & i : framebuffer) i |=HIGHLIGHT_TEXT;
    else for(char & i : framebuffer) i &=~HIGHLIGHT_TEXT;
    return framebuffer;
}
