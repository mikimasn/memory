#include "../UI/Window.h"
#include "../../game/Game.h"
#include "../MaterialDesign/Card.h"

namespace Memory::tui {
    class GameScreen: public Sheet {
    private:
        static GameScreen *instance;
        Memory::game::Game *game=nullptr;
        std::vector<Card> cards;
    public:
        explicit GameScreen(const ElementParent &parent, Memory::game::Game *game) : Sheet(parent), game(game) {
            instance = this;
            attachGame(game);
        };
        explicit GameScreen(const ElementParent &parent) : Sheet(parent) {
            instance = this;
        };
        void attachGame(Memory::game::Game *gameptr) {
            this->game = gameptr;
            auto gameCards = game->getCards();
            this->cards.clear();
            for(short & gameCard : gameCards){
                this->cards.emplace_back(gameCard);
            }
            for (int i = 0; i < gameCards.size(); i++) {
                this->cards[i].setFliped(false);
                this->cards[i].setFocus(false);
                this->cards[i].updateParent({this, this->addChild(&this->cards[i], i % 6 * 8, i / 6 * 8)});
            }
        }
        static GameScreen *getInstance() {
            return instance;
        }
    };
}
