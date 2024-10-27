#pragma once

#include "../UI/Element.h"
#include "Text.h"

namespace Memory::tui {
    struct InputRestrictions {
        bool allowNumbers = true;
        bool allowLetters = true;
        bool allowSpecialChars = true;
        bool allowSpace = true;
    };

    class InputBox : public Element {
    private:
        Text textElement;
        int pointer = 0;

        void init(const ElementSize &size);

        InputRestrictions restrictions;
    public:
        explicit InputBox(const ElementSize &size, const ElementParent &parent, InputRestrictions restrictions = {})
                : Element(size, parent), textElement({size.width, 1}, {this, this->addChild(&textElement, 0, 0)}, ""),
                  restrictions(restrictions) {
            init(size);
        };

        explicit InputBox(const ElementSize &size, InputRestrictions restrictions = {}) : Element(size),
                                                                                          textElement({size.width, 1},
                                                                                                      {this,
                                                                                                       this->addChild(
                                                                                                               &textElement,
                                                                                                               0, 0)},
                                                                                                      ""),
                                                                                          restrictions(restrictions) {
            init(size);
        };

        std::vector<char> &render(bool shouldNotifyParent) final {
            return Element::render(shouldNotifyParent);
        };

        ElementSize offerSize(ElementSize size) final {
            return currentsize;
        };

        InputActionResult handleInput(InputSignal &c) final;

        void setFocus(bool focused) final;

        bool canTakeFocus() final {
            return true;
        };

        std::string getText() {
            return std::string(textElement.text.begin(), textElement.text.begin() + pointer);
        };

        void setInput(std::string input) {
            for (int i = 0; i < (int)input.size(); i++) {
                textElement.text[i] = input[i];
            }
            pointer = (int)input.size();
            this->render(true);
        }
    };
}


