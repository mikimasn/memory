#include "../UI/Element.h"
#include "../Functional/Input.h"
#include <string>
#include <utility>
using namespace std;
namespace Memory::tui{
    class Button: public Element {
        private:
            std::string text;
            //variable of type void function pointer
            void (*callback)();
            bool isFocused = false;
        public:
            explicit Button(const ElementSize& size, const ElementParent& parent, std::string  text, void (*callback)()): Element(size, parent), text(std::move(text)), callback(callback){};
            explicit Button(const ElementSize& size, std::string  text, void (*callback)()): Element(size), text(std::move(text)), callback(callback){};
            std::vector<char>& render(bool shouldNotifyParent) final;
            ElementSize offerSize(ElementSize size) final{
                return currentsize;
            };
            InputActionResult handleInput(InputSignal& c) final;
            void setFocus(bool focused) final;
    };
}
