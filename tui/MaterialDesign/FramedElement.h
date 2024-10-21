#pragma once
#include "../UI/Element.h"

namespace Memory::tui {

    class FramedElement: public Element {
    private:
        char c;
        void registerChild(Element* child){
            child->updateParent(ElementParent(this, this->addChild(child, 1, 1)));
        };
    public:
        FramedElement(const ElementSize& size, char c): Element(size), c(c){};
        FramedElement(Element* child, char c): Element((ElementSize){child->getSize().width+2, child->getSize().height+2}), c(c){
            registerChild(child);
        };
        FramedElement(Element* child, char c, const ElementParent& parent): Element((ElementSize){child->getSize().width+2, child->getSize().height+2}, parent), c(c){
            registerChild(child);
        };
        FramedElement(const ElementSize& size, char c, const ElementParent& parent): Element(size, parent), c(c){};
        std::vector<char>& render(bool shouldNotifyParent) final;
        ElementSize offerSize(ElementSize size) final{
            return currentsize;
        };
        InputActionResult handleInput(InputSignal& c) final{
            return Element::handleInput(c);
        };
        void setFocus(bool focused) final {};
        bool canTakeFocus() final{
            return Element::canTakeFocus();
        }
    };

}
