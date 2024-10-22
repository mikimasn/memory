#include "../../game/Application.h"

namespace Memory::tui {
    SetupScreen *SetupScreen::instance = nullptr;

    void SetupScreen::startGame() {
        if(getInstance()->player1.getText().empty() || getInstance()->player2.getText().empty()){
            Memory::game::Application::throwError("Players cannot have empty names");
            return;
        }
        if(getInstance()->player1.getText()==getInstance()->player2.getText()){
            Memory::game::Application::throwError("Players cannot have the same name");
            return;
        }
        if(getInstance()->width.getText().empty() || getInstance()->height.getText().empty()){
            Memory::game::Application::throwError("Width and height cannot be empty");
            return;
        }
        int width = std::stoi(getInstance()->width.getText());
        int height = std::stoi(getInstance()->height.getText());
        if(width<2 || height<2){
            Memory::game::Application::throwError("Width and height must be at least 2");
            return;
        }
        if(width%2&&height%2){
            Memory::game::Application::throwError("Width or height must be even");
            return;
        }
        if(width*9>getInstance()->getSize().width || height*5+10>getInstance()->getSize().height){
            Memory::game::Application::throwError("Board is too big for the screen");
            return;
        }
        Memory::game::Application::throwError("Not implemented yet");
    }
}
