#include "Element.h"
#include <stack>

namespace Memory::tui{
    class Window: public Element {
    private:
        std::vector<int> focusStack;
    public:
        explicit Window(): Element(TerminalHelper::getTerminalInfo()){};
        std::vector<char>& render(bool shouldNotifyParent) final;
        ElementSize offerSize(ElementSize size) final;
        void pushFocus(int index){
            focusStack.push_back(index);
        };
        void popFocus(){
            focusStack.pop_back();
        };

    };
}
