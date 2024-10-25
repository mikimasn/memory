#include "Window.h"

namespace Memory::tui {
    Window *Window::instance = nullptr;

    std::vector<char> &Window::render(bool shouldNotifyParent) {
        for (int i: focusStack) {
            writeChildToFrameBuffer(children[i], true);
        }
        //replace nulls with spaces
        for (char &i: framebuffer) {
            if (i == 0) i = ' ';
        }
        pushToTerminal();
        return framebuffer;
    }

    ElementSize Window::offerSize(ElementSize size) {
        currentsize = size;
        this->resizeFramebuffer(size);
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
