#pragma once

#include "../UI/Window.h"
#include "../../game/Game.h"
#include "../MaterialDesign/Card.h"
#include "../MaterialDesign/Text.h"
#include "../MaterialDesign/Button.h"

namespace Memory::tui {
    class GameScreen : public Sheet {
    private:
        static GameScreen *instance;
        Memory::game::Game *game = nullptr;
        std::vector<Card> cards;
        Text player1;
        Text player2;
        Text score;
        Button saveButton;

        static void cardCallback(int id);

        static void timerCallback();

        int lastCard = -1;
        int pending = -1;

        static void saveCallback();

    public:
        explicit GameScreen(const ElementParent &parent, Memory::game::Game *game) : Sheet(parent), game(game),
                                                                                     player1({(int) game->getNames().first.size(),
                                                                                              1},
                                                                                             game->getNames().first),
                                                                                     player2({(int) game->getNames().second.size(),
                                                                                              1},
                                                                                             game->getNames().second),
                                                                                     score({10, 1}, "0 - 0"),
                                                                                     saveButton({11, 1}, "[Save Game]",
                                                                                                saveCallback) {
            instance = this;
            attachGame(game);
        };

        explicit GameScreen(const ElementParent &parent) : Sheet(parent), player1({10, 1}, "Player 1"),
                                                           player2({10, 1}, "Player 2"),
                                                           score({10, 1}, "0 - 0"),
                                                           saveButton({11, 1}, "[Save Game]", saveCallback) {
            instance = this;
        };

        void attachGame(Memory::game::Game *gameptr) {
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
                }
            }
            //save button is added last so it will be selected last by handleInput function
            saveButton.updateParent(ElementParent{this, this->addChild(&saveButton, 0, this->getSize().height - 1)});

        }

        static GameScreen *getInstance() {
            return instance;
        }

        InputActionResult handleInput(InputSignal &c) final {
            if (c.group == InputGroup::ENTER && pending != -1) return InputActionResult::VOID;
            return Sheet::handleInput(c);
        };

        std::vector<char> &render(bool shouldNotifyParent) final {
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
        };
    };
}
