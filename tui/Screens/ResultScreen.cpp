#include "ResultScreen.h"
#include "../Functional/Interupts.h"

void Memory::tui::ResultScreen::closeDialog() {
    Memory::tui::Interupts::handleTermination(0);
}

void Memory::tui::ResultScreen::update(Memory::game::GameResult result, const string &name) {
    if(result==Memory::game::GameResult::Draw) {
        Title.text = "Draw!";
        Desc.text = "The game ended in a draw!";
    }
    else {
        Title.text = name + " Wins!";
        Desc.text = name+" has won the game!";
    }

    Title.offerSize({(int) Title.text.size(), 1});
    Desc.offerSize({(int) Desc.text.size(),1});
    centerElements();
}

void Memory::tui::ResultScreen::centerElements() {
    Positioner::center(*this, this->getChild(0));
    Positioner::center(frame, frame.getChild(0),{true,false});
    Positioner::center(frame, frame.getChild(1),{true,false});
    Positioner::center(frame, frame.getChild(2),{true,false});
}
