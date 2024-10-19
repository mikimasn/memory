#include "../UI/Window.h"
#include "../Functional/Interupts.h"
#include "../MaterialDesign/Button.h"
#include "../MaterialDesign/FramedElement.h"
#include "../MaterialDesign/MemoryText.h"
#include "../MaterialDesign/Positioner.h"
#include "../MaterialDesign/Group.h"
#include <string>

namespace Memory::tui {
    class StartScreen : public Sheet {
    private:
        static void exitCallback() {
            Interupts::handleTermination(0);
        }

        static void startCallback();

        static void loadCallback();

        Button closeButton;
        Button startButton;
        Button loadButton;
        FramedElement group;
        MemoryText title;
        Group upperpart;
        Group lowerpart;
        static StartScreen *instance;
    public:
        explicit StartScreen(const ElementParent &parent) : Sheet(parent),
                                                            closeButton(ElementSize{18, 1}, std::string("Close     "),
                                                                        exitCallback),
                                                            startButton(ElementSize{18, 1}, std::string("Start game"),
                                                                        startCallback),
                                                            loadButton(ElementSize{18, 1}, std::string("Load game "),
                                                                       loadCallback),
                                                            upperpart(ElementSize{this->getSize().width,
                                                                                  this->getSize().height / 3},
                                                                      ElementParent{this,
                                                                                    this->addChild(&upperpart, 0, 0)}),
                                                            lowerpart(ElementSize{this->getSize().width,
                                                                                  this->getSize().height -
                                                                                  this->getSize().height / 3},
                                                                      ElementParent{this,
                                                                                    this->addChild(&lowerpart, 0,
                                                                                                   this->getSize().height /
                                                                                                   3)}),
                                                            group(ElementSize{20, 5}, '#'),
                                                            title(){
            startButton.updateParent(ElementParent{&group, group.addChild(&startButton, 1, 1)});
            loadButton.updateParent(ElementParent{&group, group.addChild(&loadButton, 1, 2)});
            closeButton.updateParent(ElementParent{&group, group.addChild(&closeButton, 1, 3)});
            title.updateParent(ElementParent{&upperpart, upperpart.addChild(&title, 0, 0)});
            group.updateParent(ElementParent{&lowerpart, lowerpart.addChild(&group, 0, 0)});
            Positioner::center(lowerpart,lowerpart.getChild(0));
            Positioner::center(upperpart,upperpart.getChild(0));
            instance = this;
        };
    };
}
