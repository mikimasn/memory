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
            this->cards.reserve(gameCards.size());
            for(short & gameCard : gameCards){
                this->cards.emplace_back(gameCard);
            }
            for (int i = 0; i < gameCards.size(); i++) {
                this->cards[i].setFliped(false);
                this->cards[i].setFocus(false);
            }
            auto dim = game->getDimensions();
            int width = dim.first;
            int height = dim.second;
            int cardWidth = 6, cardHeight = 6, cardSpacing = 1;
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    int index = i*width+j;
                    if(index>=gameCards.size()){
                        break;
                    }
                    this->cards[index].updateParent(ElementParent{this, this->addChild(&this->cards[index], j*(cardWidth+cardSpacing), i*(cardHeight+cardSpacing))});
                }
            }
        }
        static GameScreen *getInstance() {
            return instance;
        }
    };
}
