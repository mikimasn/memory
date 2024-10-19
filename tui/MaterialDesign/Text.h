#include "../UI/Element.h"
#include <string>

namespace Memory::tui {

    class Text : public Element {
    private:
        std::string text;
        bool highlighted = false;
    public:
        explicit Text(const ElementSize &size, const ElementParent &parent, std::string text) : Element(size, parent), text(std::move(text)) {};

        explicit Text(const ElementSize &size, std::string text) : Element(size), text(std::move(text)) {};

        std::vector<char> &render(bool shouldNotifyParent) final;

        ElementSize offerSize(ElementSize size) final {
            currentsize = size;
            framebuffer.resize(size.width * size.height);
            return currentsize;
        }

        void setFocus(bool focused) final {};
        void setHighlighted(bool highlighted, bool rerender = true) {
            this->highlighted = highlighted;
            if(rerender) render(true);
        }



    };

}