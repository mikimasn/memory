#include "Application.h"

Memory::tui::Window Memory::game::Application::window;
Memory::tui::StartScreen Memory::game::Application::startScreen = Memory::tui::StartScreen(Memory::tui::ElementParent{&window, window.addChild(&startScreen, 0, 0)});
Memory::tui::SetupScreen Memory::game::Application::setupScreen = Memory::tui::SetupScreen(Memory::tui::ElementParent{&window, window.addChild(&setupScreen, 0, 0)});
Memory::tui::ErrorScreen Memory::game::Application::errorScreen = Memory::tui::ErrorScreen(Memory::tui::ElementParent{&window, window.addChild(&errorScreen, 0, 0)},"");
bool Memory::game::Application::isError = false;
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
    window.render(true);
}

void Memory::game::Application::throwError(const string &message) {
    errorScreen.updateMessage(message);
    window.pushFocus(Screens::Error);
    window.render(true);
    isError = true;
}

void Memory::game::Application::closeError() {
    if(!isError) return;
    window.popFocus();
    window.render(true);
    isError = false;
}
