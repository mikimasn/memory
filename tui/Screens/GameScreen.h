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

        void attachGame(Memory::game::Game *gameptr);

        static GameScreen *getInstance() {
            return instance;
        }

        InputActionResult handleInput(InputSignal &c) final {
            if (c.group == InputGroup::ENTER && pending != -1) return InputActionResult::VOID;
            return Sheet::handleInput(c);
        };

        std::vector<char> &render(bool shouldNotifyParent) final;
    };
}
