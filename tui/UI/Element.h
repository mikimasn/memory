#pragma once

#include <vector>
#include "../Functional/Input.h"
#include "../TerminalHelper.h"

namespace Memory::tui {
    class Element;

    struct ElementSize {
        int width;
        int height;
    };
    struct ElementChild {
        int x;
        int y;
        bool visible;
        Element *element;
        int id;
    };

    struct ElementParent {
        Element *element;
        int childIndex;

        ElementParent(Element *parent, int childIndex) : element(parent), childIndex(childIndex) {};
    };

    class Element {
    private:
        void init();

    protected:
        std::vector<ElementChild> children;
        int childernIndex = 0;
        ElementParent parent;

        void writeChildToFrameBuffer(const ElementChild &child, bool shouldRender = false);

        void notifyParent();

        std::vector<char> framebuffer;
        std::vector<int> focusOrder;
        ElementSize currentsize;
        int focusIndex = -1;
    public:
        explicit Element(const ElementSize &size, const ElementParent &parent) : parent(parent), currentsize(size) {
            init();
        };

        explicit Element(const ElementSize &size) : parent(this, -1), currentsize(size) {
            init();
        };

        explicit Element(const TerminalInfo &terminalInfo) : parent(this, -1),
                                                             currentsize({terminalInfo.width, terminalInfo.height}) {
            init();
        };

        explicit Element(const TerminalInfo &terminalInfo, const ElementParent &parent) : parent(parent), currentsize(
                {terminalInfo.width, terminalInfo.height}) {
            init();
        };

        int addChild(Element *element, int x, int y);

        virtual void setFocus(bool focused) = 0;

        ElementChild &getChild(int index);

        virtual std::vector<char> &render(bool shouldNotifyParent = true);

        virtual InputActionResult handleInput(InputSignal &c);

        ElementSize getSize() {
            return currentsize;
        };

        std::vector<char> &getFramebuffer() {
            return framebuffer;
        };

        virtual ElementSize offerSize(ElementSize size) = 0;

        virtual void childRenderCallback(int index);

        void updateParent(ElementParent newParent) {
            this->parent = newParent;
        };

        virtual bool canTakeFocus();

        void flushFramebuffer() {
            framebuffer.assign(currentsize.width * currentsize.height, 0);
            focusOrder.assign(currentsize.width * currentsize.height, -1);
        };

        void resizeFramebuffer(int width, int height) {
            framebuffer.resize(width * height);
            focusOrder.resize(width * height);
            flushFramebuffer();
        }

        void resizeFramebuffer(ElementSize size) {
            resizeFramebuffer(size.width, size.height);
        }
    };

}

