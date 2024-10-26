#pragma once

#include "../UI/Window.h"
#include "../MaterialDesign/Text.h"
#include "../MaterialDesign/Button.h"
#include "../MaterialDesign/FramedElement.h"
#include "../MaterialDesign/Positioner.h"

namespace Memory::tui {
    class ErrorScreen : public Sheet {
    private:
        Text errorText;
        Text errorDescription;
        Button closeButton;
        FramedElement frame;
        FramedElement outerFrame;

        static void closeError();

        ErrorScreen *instance;

        void centerElements();

    public:
        explicit ErrorScreen(const ElementParent &parent, const std::string &message) : Sheet(parent),
                                                                                        errorText({6, 1}, "Error!!"),
                                                                                        errorDescription(
                                                                                                {(int) message.size(),
                                                                                                 1}, message),
                                                                                        closeButton({7, 1}, "[Close]",
                                                                                                    closeError),
                                                                                        frame({max(
                                                                                                (int) message.size() +
                                                                                                4, 40), 7}, '#'),
                                                                                        outerFrame(
                                                                                                {max((int) message.size() +
                                                                                                     6, 42), 9}, ' ') {
            outerFrame.updateParent(ElementParent{this, this->addChild(&outerFrame, 0, 0)});
            frame.updateParent(ElementParent{&outerFrame, outerFrame.addChild(&frame, 1, 1)});
            errorDescription.updateParent(ElementParent{&frame, frame.addChild(&errorDescription, 2, 3)});
            errorText.updateParent(ElementParent{&frame, frame.addChild(&errorText, 2, 1)});
            closeButton.updateParent(ElementParent{&frame, frame.addChild(&closeButton, 2, 5)});
            centerElements();
            instance = this;
        }

        ErrorScreen *getInstance() {
            return instance;
        }

        void updateMessage(const std::string &message) {
            errorDescription.offerSize({(int) message.size(), 1});
            frame.offerSize({max((int) message.size() + 4, 40), 7});
            outerFrame.offerSize({max((int) message.size() + 6, 42), 9});
            centerElements();
            errorDescription.text = message;
        }

        std::vector<char> &render(bool shouldNotifyParent) final;

    };
}
