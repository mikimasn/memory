#include "Window.h"

namespace Memory::tui {
    Window* Window::instance = nullptr;
    std::vector<char> &Window::render(bool shouldNotifyParent) {
        for(int i=focusStack.size()-1; i>=0; i--){
            writeChildToFrameBuffer(children[focusStack[i]], true);
        }
        pushToTerminal();
        return framebuffer;
    }

    ElementSize Window::offerSize(ElementSize size) {
        currentsize=size;
        framebuffer.resize(size.width*size.height);
        return currentsize;
    }

    void Window::pushToTerminal() {
        TerminalHelper::clearScreen();
        TerminalHelper::pushToTerminal(framebuffer);
    }
    void Window::childRenderCallback(int index) {
        Element::childRenderCallback(index);
        pushToTerminal();
    }

}
