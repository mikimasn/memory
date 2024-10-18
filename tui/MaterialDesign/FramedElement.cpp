#include "FramedElement.h"
std::vector<char> &Memory::tui::FramedElement::render(bool shouldNotifyParent) {
    {
        framebuffer.assign(currentsize.width * currentsize.height, ' ');
        for(int i=0; i<currentsize.width; i++){
            framebuffer[i]=c;
            framebuffer[(currentsize.height-1)*currentsize.width+i]=c;
        }
        for(int i=0; i<currentsize.height; i++){
            framebuffer[i*currentsize.width]=c;
            framebuffer[i*currentsize.width+currentsize.width-1]=c;
        }
        return Element::render(shouldNotifyParent);
    };
}