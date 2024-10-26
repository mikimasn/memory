#pragma once

#include "../UI/Element.h"

namespace Memory::tui {
    class Group : public Element {
    public:
        explicit Group(const ElementSize &size, const ElementParent &parent) : Element(size, parent) {};

        explicit Group(const ElementSize &size) : Element(size) {};

        std::vector<char> &render(bool shouldNotifyParent) final {
            return Element::render(shouldNotifyParent);
        }

        ElementSize offerSize(ElementSize size) final {
            currentsize = size;
            this->resizeFramebuffer(size);
            return currentsize;
        }

        void setFocus(bool focused) final {

        };

        bool canTakeFocus() final {
            return Element::canTakeFocus();
        }

        InputActionResult handleInput(InputSignal &c) final {
            return Element::handleInput(c);
        }
    };
}