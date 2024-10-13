#include <stdexcept>
#include <algorithm>
#include "Element.h"

namespace Memory::tui{
    int Element::addChild(Memory::tui::Element &element, int x, int y) {
        if(&element==this){
            throw std::invalid_argument("Cannot add self as child");
        }
        children.push_back({x, y, true, element,childernIndex});
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

    InputActionResult Element::handleInput(InputSignal& c) {
        auto res = InputActionResult::NOT_HANDLED;

        if(focusIndex!=-1){
            res = children[focusIndex].element.handleInput(c);
        }
        else if(children.size()>0){
            focusIndex = 0;
            children[focusIndex].element.setFocus(true);
            children[focusIndex].element.handleInput(c);
            return InputActionResult::VOID;
        }
        if(res!=InputActionResult::NOT_HANDLED) return res;
        if(c.group==InputGroup::ARROW_KEYS){
            auto key = InputHandler::convertArrowKeys(c);
            std::pair<int,int> newFocus = {0,0};
            switch(key){
                case InputActionResult::MOVE_UP:
                    newFocus = {0,-1};
                    break;
                case InputActionResult::MOVE_DOWN:
                    newFocus = {0,1};
                    break;
                case InputActionResult::MOVE_LEFT:
                    newFocus = {-1,0};
                    break;
                case InputActionResult::MOVE_RIGHT:
                    newFocus = {1,0};
                    break;
                default:
                    break;
            }
            std::vector<std::pair<int,int>> focusableChildren;
            for(int i=0; i<childernIndex; i++){
                if(i==focusIndex) continue;
                if(children[i].visible){
                    int yfactor = (children[i].y-children[focusIndex].y)*newFocus.second;
                    int xfactor = (children[i].x-children[focusIndex].x)*newFocus.first;
                    if(yfactor>0||xfactor>0) focusableChildren.push_back({(yfactor*yfactor)+(xfactor*xfactor),i});
                }
            }
            if(focusableChildren.size()==0) return InputActionResult::NOT_HANDLED;
            children[focusIndex].element.setFocus(false);
            std::sort(focusableChildren.begin(), focusableChildren.end());
            focusIndex=focusableChildren[0].second;
            children[focusIndex].element.setFocus(true);
            return InputActionResult::VOID;
        }
        return res;

    }

    void Element::init() {
        framebuffer.resize(currentsize.width*currentsize.height);
    }

}
