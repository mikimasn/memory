#pragma once

#include "../UI/Element.h"

namespace Memory::tui {
    class Group : public Element {
    public:
        explicit Group(const ElementSize &size, const ElementParent &parent) : Element(size, parent) {};

        std::vector<char> &render(bool shouldNotifyParent) final {
            return Element::render(shouldNotifyParent);
        }

        ElementSize offerSize(ElementSize size) final {
            currentsize = size;
            framebuffer.resize(size.width * size.height);
            return currentsize;
        }

        void setFocus(bool focused) final {};

        bool canTakeFocus() final {
            return Element::canTakeFocus();
        }
    };
}