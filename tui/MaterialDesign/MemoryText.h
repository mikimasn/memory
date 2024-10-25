#pragma once

#include "../UI/Element.h"

namespace Memory::tui {

    class MemoryText : public Element {
    private:

    public:
        explicit MemoryText(const ElementParent &parent) : Element(ElementSize{67, 12}, parent) {};

        explicit MemoryText() : Element(ElementSize{67, 12}) {};

        std::vector<char> &render(bool shouldNotifyParent) final;

        ElementSize offerSize(ElementSize size) final {
            currentsize = size;
            this->resizeFramebuffer(size);
            return currentsize;
        }

        void setFocus(bool focused) final {};

        bool canTakeFocus() final {
            return false;
        }
    };

}