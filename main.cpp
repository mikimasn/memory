#include "tui/UI/Window.h"
#include <armadillo>

class TestElement : public Memory::tui::Element{
    char c='X';
    public:
        explicit TestElement(const Memory::tui::ElementSize &size, const Memory::tui::ElementParent &parent) : Element(size, parent) {}
        std::vector<char>& render(bool shouldNotifyParent) final{
            for(int i=0; i<currentsize.width*currentsize.height; i++){
                framebuffer[i] = c;
            }
            return Element::render(shouldNotifyParent);
        }
        Memory::tui::ElementSize offerSize(Memory::tui::ElementSize size) override {
            return currentsize;
        }
        Memory::tui::InputActionResult handleInput(Memory::tui::InputSignal &c) override {
            return Memory::tui::InputActionResult::NOT_HANDLED;
        }
        void setFocus(bool focused) override {
            c = focused ? 'O' : 'X';
            render(true);
        }
};
int main() {
    Memory::tui::Window window;
    Memory::tui::Sheet sheet({window, window.addChild(sheet, 0, 0)});
    TestElement child({5, 5}, {sheet, sheet.addChild(child, 0, 0)});
    TestElement child2({5, 5}, {sheet, sheet.addChild(child2, 20, 0)});
    window.pushFocus(0);
    window.render(true);
    sleep(1);
    Memory::tui::InputSignal signal = {Memory::tui::InputGroup::ARROW_KEYS, 2};
    window.handleInput(signal);
    sleep(1);
    window.handleInput(signal);
    sleep(1);
    return 0;
}
