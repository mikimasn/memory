#include "../UI/Element.h"
#include "../Functional/Input.h"
#include "Text.h"
#include <string>
#include <utility>
using namespace std;
namespace Memory::tui{
    class Button: public Element {
        private:
            //variable of type void function pointer
            void (*callback)();
            bool isFocused = false;
            void init();
            Text textElement;
        public:
            explicit Button(const ElementSize& size, const ElementParent& parent, const std::string&  text, void (*callback)()): Element(size, parent), callback(callback),
                                                                                                                          textElement({(int)text.size(),1},{this,this->addChild(&textElement,0,0)},text){
                init();
            };
            explicit Button(const ElementSize& size,const std::string&  text, void (*callback)()): Element(size), callback(callback), textElement({(int)text.size(),1},{this,this->addChild(&textElement,0,0)},text){
                init();
            };
            std::vector<char>& render(bool shouldNotifyParent) final;
            ElementSize offerSize(ElementSize size) final{
                return currentsize;
            };
            InputActionResult handleInput(InputSignal& c) final;
            void setFocus(bool focused) final;
    };
}
