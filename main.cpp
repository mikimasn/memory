#include "tui/UI/Window.h"
#include "tui/MaterialDesign/FramedElement.h"
#include "tui/Functional/Interupts.h"
#include "tui/MaterialDesign/Button.h"
#include "tui/MaterialDesign/Positioner.h"
#include <armadillo>

class TestElement : public Memory::tui::Element{
    char c='.';
    public:
        explicit TestElement(const Memory::tui::ElementSize &size, const Memory::tui::ElementParent &parent) : Element(size, parent) {}
        explicit TestElement(const Memory::tui::ElementSize &size) : Element(size) {}
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
//            c = focused ? 'O' : 'X';
            render(true);
        }
};
void klik(){
    Memory::tui::Interupts::handleTermination(0);
}
int main() {
    Memory::tui::Window window;
    Memory::tui::Sheet background({&window, window.addChild(&background, 0, 0)});
    TestElement testElement(background.getSize(), Memory::tui::ElementParent{&background, background.addChild(&testElement, 0, 0)});
    Memory::tui::Sheet sheet({&window, window.addChild(&sheet, 0, 0)});

    Memory::tui::FramedElement group(Memory::tui::ElementSize{20,7},'#',Memory::tui::ElementParent{&sheet, sheet.addChild(&group, 0, 0)});
    vector<Memory::tui::Button> buttons;
    for(int i=0;i<5;i++){
        Memory::tui::Button button(Memory::tui::ElementSize{18,1}, "Button "+std::to_string(i), klik);
        buttons.push_back(button);
    }
    for(int i=0;i<5;i++) buttons[i].updateParent(Memory::tui::ElementParent(&group, group.addChild(&buttons[i], 1, i+1)));
    Memory::tui::Positioner::center(sheet, sheet.getChild(0));
    Memory::tui::Interupts::setupInterupts();
    window.pushFocus(0);
    window.pushFocus(1);
    window.render(true);
    while(true){
        auto ele = Memory::tui::InputHandler::blockForInput();
        window.handleInput(ele);
//        window.render(true);
    }
    return 0;
}
