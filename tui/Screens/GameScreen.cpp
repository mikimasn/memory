#include "GameScreen.h"
#include "../Functional/Interupts.h"
#include "../../game/Application.h"

Memory::tui::GameScreen *Memory::tui::GameScreen::instance = nullptr;

void Memory::tui::GameScreen::cardCallback(int id) {
    auto result = instance->game->discover(id);
    if(result==Memory::game::GameAction::Score){
        instance->lastCard = -1;
    }
    else if(result==Memory::game::GameAction::Void){
        instance->lastCard = id;
        return;
    }
    else if(result==Memory::game::GameAction::SwitchPlayer){
        instance->pending=id;
        if(!Memory::tui::Interupts::callAfter(3000, timerCallback)) timerCallback();
    }
    else if(result==Memory::game::GameAction::EndGame){
        Memory::game::Application::showGameResult();
    }
}

void Memory::tui::GameScreen::timerCallback() {
    instance->cards[instance->lastCard].setFliped(false);
    instance->cards[instance->pending].setFliped(false);
    instance->lastCard = instance->pending=-1;
    instance->render(true);
}
