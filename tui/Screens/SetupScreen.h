#include "../UI/Window.h"
#include "../MaterialDesign/InputBox.h"
#include "../MaterialDesign/FramedElement.h"
#include "../MaterialDesign/Positioner.h"
#include "../MaterialDesign/Button.h"

namespace Memory::tui {
    class SetupScreen : public Sheet {
    public:
        static SetupScreen *instance;
        InputBox player1;
        InputBox player2;
        InputBox width;
        InputBox height;
        Text firstInstruction;
        Text secondInstruction;
        Text player1Text;
        Text player2Text;
        Text widthText;
        Text heightText;
        FramedElement frame;
        Button startButton;

        static void startGame();

        explicit SetupScreen(const ElementParent &parent) : Sheet(parent),
                                                            player1({30, 1}),
                                                            player2({30, 1}),
                                                            width({2, 1}, InputRestrictions{true, false, false, false}),
                                                            height({2, 1},
                                                                   InputRestrictions{true, false, false, false}),
                                                            player1Text({9, 1}, "Player 1:"),
                                                            player2Text({9, 1}, "Player 2:"),
                                                            widthText({40, 1}, "Width:"),
                                                            heightText({40, 1}, "Height:"),
                                                            firstInstruction({38, 1},
                                                                             "Please enter the names of the players"),
                                                            secondInstruction({47, 1},
                                                                              "Please enter the width and height of the board"),
                                                            startButton({12, 1}, "[Start Game]", startGame),
                                                            frame({60, 10}, '#') {
            instance = this;
            frame.updateParent(ElementParent{this, this->addChild(&frame, 0, 0)});
            Positioner::center(*this, this->getChild(0));
            firstInstruction.updateParent(ElementParent{&frame, frame.addChild(&firstInstruction, 2, 1)});
            Positioner::center(frame, frame.getChild(0), {true, false});
            player1Text.updateParent(ElementParent{&frame, frame.addChild(&player1Text, 2, 2)});
            player2Text.updateParent(ElementParent{&frame, frame.addChild(&player2Text, 2, 3)});
            player1.updateParent(ElementParent{&frame, frame.addChild(&player1, 2 + 10, 2)});
            player2.updateParent(ElementParent{&frame, frame.addChild(&player2, 2 + 10, 3)});
            int childID;
            secondInstruction.updateParent(ElementParent{&frame, childID = frame.addChild(&secondInstruction, 2, 4)});
            Positioner::center(frame, frame.getChild(childID), {true, false});
            widthText.updateParent(ElementParent{&frame, frame.addChild(&widthText, 2, 5)});
            heightText.updateParent(ElementParent{&frame, frame.addChild(&heightText, 2, 6)});
            width.updateParent(ElementParent{&frame, frame.addChild(&width, 2 + 10, 5)});
            height.updateParent(ElementParent{&frame, frame.addChild(&height, 2 + 10, 6)});
            startButton.updateParent(ElementParent{&frame, childID = frame.addChild(&startButton, 2, 8)});
            Positioner::center(frame, frame.getChild(childID), {true, false});
        };

        static SetupScreen *getInstance() {
            return instance;
        }
    };

}

