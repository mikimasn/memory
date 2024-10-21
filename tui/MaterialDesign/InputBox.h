#include "../UI/Element.h"
#include "Text.h"

namespace Memory::tui{
    class InputBox: public Element {
    private:
        Text textElement;
        int pointer=0;
        void init(const ElementSize &size);
    public:
        explicit InputBox(const ElementSize& size, const ElementParent& parent): Element(size, parent), textElement({size.width,1},{this,this->addChild(&textElement,0,0)},""){
            init(size);
        };
        explicit InputBox(const ElementSize& size): Element(size), textElement({size.width,1},{this,this->addChild(&textElement,0,0)},""){
            init(size);
        };
        std::vector<char>& render(bool shouldNotifyParent) final{
            return Element::render(shouldNotifyParent);
        };
        ElementSize offerSize(ElementSize size) final{
            return currentsize;
        };
        InputActionResult handleInput(InputSignal& c) final;
        void setFocus(bool focused) final;
        bool canTakeFocus() final{
            return true;
        };
        std::string getText(){
            return std::string(textElement.text.begin(),textElement.text.begin()+pointer);
        };
    };
}


