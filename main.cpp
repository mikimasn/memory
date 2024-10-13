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
    Memory::tui::Window window;
    TestElement child({5, 5}, {window, window.addChild(child, 0, 0)});
    window.pushFocus(window.addChild(child, 0, 0));
    window.render(true);
    sleep(5);
    return 0;
}
