#include "../../game/Application.h"
#include "ErrorScreen.h"


void Memory::tui::ErrorScreen::closeError() {
    Memory::game::Application::closeError();
}

void Memory::tui::ErrorScreen::centerElements() {
    Positioner::center(*this, this->getChild(0));
    Positioner::center(frame, frame.getChild(0), {true, false});
    Positioner::center(frame, frame.getChild(1), {true, false});
    Positioner::center(frame, frame.getChild(2), {true, false});
}

std::vector<char> &Memory::tui::ErrorScreen::render(bool shouldNotifyParent) {
    flushFramebuffer();
    framebuffer.assign(framebuffer.size(), ' ');
    return Element::render(shouldNotifyParent);
}
