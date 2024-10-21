#include "Application.h"

Memory::tui::Window Memory::game::Application::window;
Memory::tui::StartScreen Memory::game::Application::startScreen = Memory::tui::StartScreen(Memory::tui::ElementParent{&window, window.addChild(&startScreen, 0, 0)});

void Memory::game::Application::initiliaze() {
    Memory::tui::Interupts::setupInterupts();
}

void Memory::game::Application::start() {
    initiliaze();
    window.pushFocus(0);
    window.render(true);
    while(true){
        auto ele = Memory::tui::InputHandler::blockForInput();
        window.handleInput(ele);
    }
}

void Memory::game::Application::goToSetup() {
    window.clearFocus();
    window.pushFocus(Screens::Setup);
}
