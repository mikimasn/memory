#include "../UI/Window.h"
#include "../MaterialDesign/Text.h"
#include "../MaterialDesign/Button.h"
#include "../MaterialDesign/FramedElement.h"
#include "../MaterialDesign/Positioner.h"
#include "../../game/Game.h"

namespace Memory::tui {
    class ResultScreen : public Sheet {
    private:
        Text Title;
        Text Desc;
        Button closeButton;
        FramedElement frame;
        FramedElement outerFrame;

        static void closeDialog();

        ResultScreen *instance;

        void centerElements();

    public:
        explicit ResultScreen(const ElementParent &parent, const std::string &message) : Sheet(parent),
                                                                                         Title({10, 1}, "Game Ended"),
                                                                                         Desc({(int) message.size(), 1},
                                                                                              message),
                                                                                         closeButton({7, 1}, "[Close]",
                                                                                                     closeDialog),
                                                                                         frame({max(
                                                                                                 (int) message.size() +
                                                                                                 4, 40), 7}, '#'),
                                                                                         outerFrame(
                                                                                                 {max((int) message.size() +
                                                                                                      6, 42), 9}, ' ') {
            outerFrame.updateParent(ElementParent{this, this->addChild(&outerFrame, 0, 0)});
            frame.updateParent(ElementParent{&outerFrame, outerFrame.addChild(&frame, 1, 1)});
            Desc.updateParent(ElementParent{&frame, frame.addChild(&Desc, 2, 3)});
            Title.updateParent(ElementParent{&frame, frame.addChild(&Title, 2, 1)});
            closeButton.updateParent(ElementParent{&frame, frame.addChild(&closeButton, 2, 5)});
            centerElements();
            instance = this;
        }

        ResultScreen *getInstance() {
            return instance;
        }

        void update(Memory::game::GameResult result, const std::string &name = "");
    };
}
