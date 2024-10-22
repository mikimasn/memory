#include "../UI/Element.h"
#include "FramedElement.h"
#include "Group.h"

namespace Memory::tui{

    class Card: public Element{
    private:
        bool isFlipped = false;
        bool isMatched = false;
        bool isFocused = false;
        short front;
        FramedElement frame;
    public:
        explicit Card(const ElementParent &parent, short front) : Element(ElementSize{6,6}, parent), front(front), frame(ElementSize{6,6},'?'){
            frame.updateParent({this, this->addChild(&frame, 0, 0)});
        };
        explicit Card(short front) : Element(ElementSize{6,6}), front(front), frame(ElementSize{6,6},'?'){
            frame.updateParent({this, this->addChild(&frame, 0, 0)});
        };
        void setFocus(bool focused) final {
            isFocused = focused;
            this->render(true);
        };
        InputActionResult handleInput(InputSignal &signal) final;
        std::vector<char> &render(bool shouldNotifyParent) final;
        ElementSize offerSize(ElementSize size) final {
            currentsize = size;
            framebuffer.resize(size.width * size.height);
            return currentsize;
        };
        bool canTakeFocus() final {
            return !isMatched;
        };
        void setFliped(bool fliped){
            isFlipped = fliped;
            this->render(true);
        };
    };
}
