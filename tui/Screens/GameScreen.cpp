#include "GameScreen.h"
#include "../Functional/Interupts.h"
#include "../../game/Application.h"

Memory::tui::GameScreen *Memory::tui::GameScreen::instance = nullptr;

void Memory::tui::GameScreen::cardCallback(int id) {
    auto result = instance->game->discover(id);
    if (result == Memory::game::GameAction::Score) {
        instance->lastCard = -1;
        instance->render(true);
    } else if (result == Memory::game::GameAction::Void) {
        instance->lastCard = id;
        return;
    } else if (result == Memory::game::GameAction::SwitchPlayer) {
        instance->pending = id;
        if (!Memory::tui::Interupts::callAfter(2000, timerCallback)) timerCallback();
    } else if (result == Memory::game::GameAction::EndGame) {
        Memory::game::Application::showGameResult();
    }
}

void Memory::tui::GameScreen::timerCallback() {
    instance->cards[instance->lastCard].setFliped(false);
    instance->cards[instance->pending].setFliped(false);
    instance->lastCard = instance->pending = -1;
    instance->render(true);
}

void Memory::tui::GameScreen::saveCallback() {
    Memory::game::Application::showSaveDialog();
}

void Memory::tui::GameScreen::attachGame(Memory::game::Game *gameptr) {
    this->game = gameptr;
    player1.text = game->getNames().first;
    player2.text = game->getNames().second;
    player1.offerSize({(int) game->getNames().first.size(), 1});
    player2.offerSize({(int) game->getNames().second.size() + 1, 1});
    player1.updateParent(ElementParent{this, this->addChild(&player1, 0, 0)});
    player2.updateParent(
            ElementParent{this, this->addChild(&player2, (int) game->getNames().first.size() + 1, 0)});
    score.updateParent(ElementParent{this, this->addChild(&score, (int) (game->getNames().first.size() +
                                                                         game->getNames().second.size()) + 3,
                                                          0)});
    auto gameCards = game->getCards();
    this->cards.clear();
    this->cards.reserve(gameCards.size());
    for (int i = 0; i < gameCards.size(); i++) {
        this->cards.emplace_back(gameCards[i], cardCallback, i);
    }
    for (int i = 0; i < gameCards.size(); i++) {
        this->cards[i].setFliped(false);
        this->cards[i].setFocus(false);
    }
    auto dim = game->getDimensions();
    int width = dim.first;
    int height = dim.second;
    int cardWidth = 6, cardHeight = 6, cardhspacing = 1, cardvspacing = 1;
    auto size = this->getSize();
    cardvspacing = (size.height - height * cardHeight) / height;
    cardhspacing = (size.width - width * cardWidth) / width;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            if (index >= gameCards.size()) {
                break;
            }
            this->cards[index].updateParent(ElementParent{this, this->addChild(&this->cards[index],
                                                                               j * (cardWidth + cardhspacing),
                                                                               i * (cardHeight + cardvspacing) +
                                                                               1)});
            if (game->isDiscovered(index)) {
                this->cards[index].setFliped(true);
            }
        }
    }
    //save button is added last so it will be selected last by handleInput function
    saveButton.updateParent(ElementParent{this, this->addChild(&saveButton, 0, this->getSize().height - 1)});

}

std::vector<char> &Memory::tui::GameScreen::render(bool shouldNotifyParent) {
    if (game != nullptr) {
        score.text = std::to_string(game->getScores().first) + " - " + std::to_string(game->getScores().second);
        if (game->getCurrentPlayer() == 0) {
            player1.setHighlighted(true);
            player2.setHighlighted(false);
        } else {
            player1.setHighlighted(false);
            player2.setHighlighted(true);
        }
    }
    return Sheet::render(shouldNotifyParent);
}
