#include <stdexcept>
#include "Element.h"

namespace Memory::tui{
    int Element::addChild(Memory::tui::Element &element, int x, int y) {
        if(&element==this){
            throw std::invalid_argument("Cannot add self as child");
        }
        children.push_back({x, y, true, element});
        return childernIndex++;
    }

    ElementChild &Element::getChild(int index) {
        if(index>=childernIndex){
            throw std::out_of_range("Index out of range");
        }
        return children[index];
    }

    std::vector<char>& Element::render(bool shouldNotifyParent) {
        //go over every child and render it
        for(const auto& child : children){
            writeChildToFrameBuffer(child, true);
        }
        if(shouldNotifyParent){
            notifyParent();
        }
        return framebuffer;
    }

    void Element::childRenderCallback(int index) {
        writeChildToFrameBuffer(getChild(index), false);
        //Frame buffer has been updated, notify parent
        notifyParent();
    }

    void Element::writeChildToFrameBuffer(const ElementChild &child, bool shouldRender) {
        if(child.visible){
            auto childFrameBuffer = child.element.getFramebuffer();
            if(shouldRender){
                childFrameBuffer = child.element.render(false);
            }
            auto childSize = child.element.getSize();
            for(int row=0; row<childSize.height; row++){
                int relativeRow = row+child.y;
                if(relativeRow>=currentsize.height) break; //we are out of bounds for the parent
                for(int col=0; col<childSize.width; col++){
                    int relativeCol = col+child.x;
                    if(relativeCol>=currentsize.width) break;
                    int resultCell = relativeRow*currentsize.width+relativeCol;
                    int childCell = row*childSize.width+col;
                    framebuffer[resultCell] = childFrameBuffer[childCell];
                }
            }
        }
    }

    void Element::notifyParent() {
        if(parent.childIndex!=-1){
            parent.element.childRenderCallback(parent.childIndex);
        }
    }

    InputActionResult Element::handleInput(char c) {
        //Not implemented
        return InputActionResult::VOID;
    }

}
