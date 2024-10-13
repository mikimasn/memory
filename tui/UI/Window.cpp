#include "Window.h"

namespace Memory::tui {
    std::vector<char> &Window::render(bool shouldNotifyParent) {
        framebuffer.assign(currentsize.width * currentsize.height, ' ');
        for(int i=focusStack.size()-1; i>=0; i--){
            writeChildToFrameBuffer(children[focusStack[i]], true);
        }
        TerminalHelper::clearScreen();
        TerminalHelper::pushToTerminal(framebuffer);
        return framebuffer;
    }

    ElementSize Window::offerSize(ElementSize size) {
        currentsize=size;
        framebuffer.resize(size.width*size.height);
        return currentsize;
    }

}
