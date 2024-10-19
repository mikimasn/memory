#include "tui/UI/Window.h"
#include "tui/Screens/StartScreen.h"
#include <armadillo>

int main() {
    Memory::tui::Window window;
    Memory::tui::StartScreen startScreen(Memory::tui::ElementParent{&window, window.addChild(&startScreen, 0, 0)});
    Memory::tui::Interupts::setupInterupts();
//    window.pushFocus(0);
    window.pushFocus(0);
    window.render(true);
    while(true){
        auto ele = Memory::tui::InputHandler::blockForInput();
        window.handleInput(ele);
    }
    return 0;
}
