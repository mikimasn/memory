#pragma once
#include "Element.h"
#include <stack>

namespace Memory::tui{
    class Sheet: public Element{
    public:
        explicit Sheet(const ElementParent parent): Element(TerminalHelper::getTerminalInfo(),parent){};
        std::vector<char>& render(bool shouldNotifyParent) final{
            framebuffer.assign(currentsize.width * currentsize.height, 0);
            return Element::render(shouldNotifyParent);
        };
        ElementSize offerSize(ElementSize size) final{
            return currentsize;
        };
        InputActionResult handleInput(InputSignal& c) final{
            return Element::handleInput(c);
        };
        void setFocus(bool focused) final {};
    };
    class Window: public Element {
    private:
        std::vector<int> focusStack;
        static Window* instance;
    protected:
        void pushToTerminal();
    public:
        explicit Window(): Element(TerminalHelper::getTerminalInfo()){
            Memory::tui::TerminalHelper::setupTerminal();
            Window::instance=this;
        };
        std::vector<char>& render(bool shouldNotifyParent) final;
        ElementSize offerSize(ElementSize size) final;
        void pushFocus(int index){
            focusStack.push_back(index);
        };
        void popFocus(){
            focusStack.pop_back();
        };
        void clearFocus(){
            focusStack.clear();
        };
        InputActionResult handleInput(InputSignal& c) final{
            return children[focusStack[focusStack.size()-1]].element->handleInput(c);
        };
        void setFocus(bool focused) final {};

        void childRenderCallback(int index) final;
        static Window *getInstance(){
            return instance;
        };
    };
}
