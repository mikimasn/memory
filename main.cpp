#include "tui/UI/Window.h"
#include <iostream>
#include <armadillo>

class TestElement : public Memory::tui::Element{
    public:
        explicit TestElement(const Memory::tui::ElementSize &size, const Memory::tui::ElementParent &parent) : Element(size, parent) {}
        std::vector<char>& render(bool shouldNotifyParent) final{
            for(int i=0; i<currentsize.width*currentsize.height; i++){
                framebuffer[i] = 'X';
            }
            return Element::render(shouldNotifyParent);
        }
        Memory::tui::ElementSize offerSize(Memory::tui::ElementSize size) override {
            return currentsize;
        }
};
int main() {
    Memory::tui::TerminalHelper::setupTerminal();
    Memory::tui::TerminalHelper::clearScreen();
    auto terminalInfo = Memory::tui::TerminalHelper::getTerminalInfo();
    if(terminalInfo.width==0 || terminalInfo.height==0){
        terminalInfo = {80, 24};
    }
    const Memory::tui::ElementSize size = {terminalInfo.width, terminalInfo.height};
    //print size
//    std::cout << "Width: " << size.width << " Height: " << size.height << std::endl;
    Memory::tui::Window window;
    TestElement child({5, 5}, {window, window.addChild(child, 0, 0)});
    window.pushFocus(window.addChild(child, 0, 0));
    window.render(true);
    sleep(5);
    return 0;
}
