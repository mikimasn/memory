#include <vector>
#include "Input.h"
#include "../TerminalHelper.h"

namespace Memory::tui {
    class Element;
    struct ElementSize{
        int width;
        int height;
    };
    struct ElementChild{
        int x;
        int y;
        bool visible;
        Element& element;
        int id;
    };
    struct ElementParent{
        Element& element;
        int childIndex;
        ElementParent(Element& parent, int childIndex) : element(parent), childIndex(childIndex){};
    };
    class Element {
    protected:
        std::vector<ElementChild> children;
        int childernIndex = 0;
        ElementParent parent;
        void writeChildToFrameBuffer(const ElementChild& child, bool shouldRender=false);
        void notifyParent();
        std::vector<char> framebuffer;
        ElementSize currentsize;
    public:
        explicit Element(const ElementSize &size,const ElementParent &parent) : parent(parent),currentsize(size){
            framebuffer.resize(size.width*size.height);
        };
        explicit Element(const ElementSize &size) : parent(*this, -1),currentsize(size){
            framebuffer.resize(size.width*size.height);
        };
        explicit Element(const TerminalInfo &terminalInfo) : parent(*this, -1),currentsize({terminalInfo.width, terminalInfo.height}){
            framebuffer.resize(terminalInfo.width*terminalInfo.height);
        };
        int addChild(Element& element, int x, int y);
        ElementChild& getChild(int index);
        virtual std::vector<char>& render(bool shouldNotifyParent=true);
        InputActionResult handleInput(char c);
        ElementSize getSize(){
            return currentsize;
        };
        std::vector<char>& getFramebuffer(){
            return framebuffer;
        };
        virtual ElementSize offerSize(ElementSize size) = 0;
        void childRenderCallback(int index);
    };

}

